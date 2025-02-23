#ifndef __BASE_UNSAFE_INSQUEUE_HH__
#define __BASE_UNSAFE_INSQUEUE_HH__

#include <cassert>
#include <string>
#include <cstdint>
#include <list>
#include "base/logging.hh"
#include "debug/Speclfb.hh"
#include "base/trace.hh"

namespace gem5
{

class Unsafe{

  protected:

    static std::list<uint64_t> unsafePC;
    

  public:
  
   
    void 
    unsafePCadd(uint64_t pc) {
        auto it = unsafePC.begin();
        while(it != unsafePC.end()) {
            if(*it == pc) {
                return;
            }
            ++it;
        }
        unsafePC.push_back(pc);
    }

    void unsafePCremove(uint64_t pc) {
        // auto it = unsafePC.begin();
        // while(it!=unsafePC.end()){
        //     if(*it==pc){
        //         unsafePC.erase(it);
        //     }
        //     ++it;
        // }
        unsafePC.remove(pc);
    }
//     void 
//     unsafeMUSLadd(uint64_t pc) {
//         auto it = unsafeMUSL.begin();
//         while(it != unsafeMUSL.end()) {
//             if(*it == pc) {
//                 return;
//             }
//             ++it;
//         }
//         unsafeMUSL.push_back(pc);
//     }

//     void 
//     unsafeMUSLprintf() {
//         auto it = unsafeMUSL.begin();
//         DPRINTF(Speclfb,"this is musl " );
//         while(it != unsafeMUSL.end()) {

//         DPRINTF(Speclfb,"%x ",*it );
//            ++it;
//         }
//      DPRINTF(Speclfb,"\n");
//     }


    

//     void unsafeMUSLremove(uint64_t pc) {
//         // auto it = unsafePC.begin();
//         // while(it!=unsafePC.end()){
//         //     if(*it==pc){
//         //         unsafePC.erase(it);
//         //     }
//         //     ++it;
//         // }
//         unsafeMUSL.remove(pc);
//     }
//    bool MUSL_check(uint64_t pc) {
//         auto it = unsafeMUSL.begin();
//         while(it != unsafeMUSL.end()){
//             if(*it == pc){
//                 return true;
//             }
//             ++it;
//         }
//         return false;
//     }
    bool speclfb_check(uint64_t pc) {
        auto it = unsafePC.begin();
        while(it != unsafePC.end()){
            if(*it == pc){
                return true;
            }
            ++it;
        }
        return false;
    }


};

}                                                                                       

#endif

