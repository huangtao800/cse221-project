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


static inline unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}



static inline void func0(){}

static inline void func1(int a1){}

static inline void func2(int a1, int a2){}

static inline void func3(int a1, int a2, int a3){}

static inline void func4(int a1, int a2, int a3, int a4){}

static inline void func5(int a1, int a2, int a3, int a4, int a5){}

static inline void func6(int a1, int a2, int a3, int a4, int a5, int a6){}

static inline void func7(int a1, int a2, int a3, int a4, int a5, int a6, int a7){}
