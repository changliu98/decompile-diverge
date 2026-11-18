void sse_dot4(float *v1, float *v2, float *result)
{
  __asm__ __volatile__ (
    "movups (%1), %%xmm0\n\t"
    "movups 16(%1), %%xmm1\n\t"
    "movups 8(%1), %%xmm2\n\t"
    "movups 24(%1), %%xmm3\n\t"
    "movups (%0), %%xmm4\n\t"
    "movups 16(%0), %%xmm5\n\t"
    "movups 8(%0), %%xmm6\n\t"
    "movups 24(%0), %%xmm7\n\t"
    "mulps %%xmm4, %%xmm0\n\t"
    "mulps %%xmm7, %%xmm1\n\t"
    "mulps %%xmm5, %%xmm2\n\t"
    "mulps %%xmm6, %%xmm3\n\t"
    "addps %%xmm1, %%xmm0\n\t"
    "addps %%xmm3, %%xmm2\n\t"
    "addps %%xmm0, %%xmm2\n\t"
    "addps %%xmm2, %%xmm0\n\t"
    "movups %%xmm0, (%2)\n\t"
    :"=m"(*result)
    :"m"(*v1), "m"(*v2)
    :"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "cc", "memory"
  );
}