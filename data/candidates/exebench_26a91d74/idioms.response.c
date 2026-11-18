void cpuid_detect(int *sse2, int *sse3)
{
  int a; int b; int c; int d;
  asm volatile (
    "mov $1, %%eax\n\t"
    "cpuid\n\t"
    "mov %%edx, %0\n\t"
    "mov %%ecx, %1\n\t"
    :"=m"(d), "=m"(c)
    :
    :"%eax", "%edx", "%ecx");
  if (sse2 != ((void *)0))
    *sse2 = d & (1 << 26);
  if (sse3 != ((void *)0))
    *sse3 = c & (1 << 0);
}