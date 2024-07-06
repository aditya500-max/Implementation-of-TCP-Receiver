#include "wrapping_integers.hh"
#include<iostream>
using namespace std;
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) { return WrappingInt32{isn + static_cast<uint32_t>(n)}; }
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {
    uint32_t count = n - isn;
    const constexpr uint64_t RAN_INT32= 1l << 32;
   
    if (count<checkpoint) {
         uint64_t a;
         uint64_t b;
         uint64_t c;
         uint64_t d;
         uint64_t e;
            a=checkpoint-count;
            b=RAN_INT32>>1;
            c=a+b;
            d=c/RAN_INT32;
            e=RAN_INT32*d+count;
            return e;
        }else{return count;}
}


