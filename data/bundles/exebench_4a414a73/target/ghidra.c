void cpuid_detect(int *sse2,int *sse3)

{
  int *sse3_local;
  int *sse2_local;
  
  if (sse2 != (int *)0x0) {
    *sse2 = 0;
  }
  if (sse3 != (int *)0x0) {
    *sse3 = 0;
  }
  return;
}