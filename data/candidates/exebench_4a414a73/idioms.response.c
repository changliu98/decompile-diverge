void cpuid_detect(int *sse2, int *sse3)
{
  if (sse2 != ((void *)0))
    *sse2 = 0;
  if (sse3 != ((void *)0))
    *sse3 = 0;
}