//
//  rdtsc.h
//  ReadTSC
//
//  Created by Tao Huang on 4/15/16.
//  Copyright © 2016 Tao Huang. All rights reserved.
//

#ifndef rdtsc_h
#define rdtsc_h


#endif /* rdtsc_h */


#if defined(__i386__)

static inline unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}
#elif defined(__x86_64__)


static inline unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#elif defined(__powerpc__)


static inline unsigned long long rdtsc(void)
{
    unsigned long long int result=0;
    unsigned long int upper, lower,tmp;
    __asm__ volatile(
                     "0:                  \n"
                     "\tmftbu   %0           \n"
                     "\tmftb    %1           \n"
                     "\tmftbu   %2           \n"
                     "\tcmpw    %2,%0        \n"
                     "\tbne     0b         \n"
                     : "=r"(upper),"=r"(lower),"=r"(tmp)
                     );
    result = upper;
    result = result<<32;
    result = result|lower;
    
    return(result);
}

#endif

static inline void func0(){}

static inline void func1(int a1){}

static inline void func2(int a1, int a2){}

static inline void func3(int a1, int a2, int a3){}

static inline void func4(int a1, int a2, int a3, int a4){}

static inline void func5(int a1, int a2, int a3, int a4, int a5){}

static inline void func6(int a1, int a2, int a3, int a4, int a5, int a6){}
