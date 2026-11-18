






static __inline void run_cpuid(int eax, int ecx, int* abcd)
{



  int ebx = 0;
  int edx = 0;
# 268 "libpopcnt.h"
    __asm__ ("cpuid;"
             : "+b" (ebx),
               "+a" (eax),
               "+c" (ecx),
               "=d" (edx));


  abcd[0] = eax;
  abcd[1] = ebx;
  abcd[2] = ecx;
  abcd[3] = edx;

}
