void cpuid(int code, int *a, int *b, int *c, int *d) {
  int eax, ebx, ecx, edx;
  __asm__ __volatile__(
      "cpuid"
      : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
      : "a"(code));
  *a = eax;
  *b = ebx;
  *c = ecx;
  *d = edx;
}