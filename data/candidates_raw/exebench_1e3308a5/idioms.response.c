void fneg(float *in, float *out)
{
  __asm__ __volatile__ (
    "movd  (%1), %%xmm0\n"
    "psraw $8, %%xmm0\n"
    "movd  %%xmm0, (%2)\n"
    :
    : "m"(*in), "r"(in), "m"(*out)
    : "memory", "xmm0"
  );
}