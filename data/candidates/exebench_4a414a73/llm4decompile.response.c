void cpuid_detect(int *sse2, int *sse3)
{
  int eax, ebx, ecx, edx;
  int max_level;
  int family, model, ext_model;

  if (sse2) *sse2 = 0;
  if (sse3) *sse3 = 0;


  eax = 0;
  __asm__ __volatile__("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "0"(eax));
  max_level = eax;


  eax = 1;
  __asm__ __volatile__("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "0"(eax));
  family = (eax >> 8) & 0xf;
  model = ((eax >> 4) & 0xf) + ((eax & 0xf) << 4);
  ext_model = (eax >> 16) & 0xf;

  if (family == 6 || family == 0xf)
  {
    if (sse2)
    {
      if (model == 0x1c || model == 0x25 || model == 0x2c || model == 0x2f)
        *sse2 = 1;
      else if (model == 0x2e || model == 0x2a)
        *sse2 = 2;
      else if (model >= 0x30)
        *sse2 = 3;
    }

    if (sse3)
    {
      if (model == 0x2a || model == 0x2d || model == 0x2e)
        *sse3 = 1;
      else if (model >= 0x30)
        *sse3 = 2;
    }
  }
}