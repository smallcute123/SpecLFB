#include "base/unsafe_insqueue.hh"

#include <cassert>
#include <string>
#include <cstdint>
#include <list>


namespace gem5
{


extern std::list<uint64_t> Unsafe::unsafePC;

void 
Unsafe::unsafePCadd(uint64_t pc){
   unsafePC.push_back(pc);
}

void 
Unsafe::unsafePCremove(uint64_t pc){
    // auto it = unsafePC.begin();
    // while(it!=unsafePC.end()){
    //     if(*it==pc){
    //         unsafePC.erase(it);
    //     }
    //     ++it;
    // }
    unsafePC.remove(pc);
}

bool 
Unsafe::speclfb_check(uint64_t pc){
    auto it = unsafePC.begin();
     while(it!=unsafePC.end()){
         if(*it==pc){
             return false;
         }
         ++it;
     }
     return true;
}
}
