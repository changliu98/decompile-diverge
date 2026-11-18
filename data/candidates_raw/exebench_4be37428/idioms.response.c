static inline void sseround(float *x)
{
  __asm__ __volatile__ (
    "andps %1, %0\n\t"
    "movd %0, %%eax\n\t"
    "movd %%eax, %0\n\t"
    "orps %2, %0\n"
    :"=r" (*x)
    :"r" (sseround_mask), "r" (zero)
    );
}