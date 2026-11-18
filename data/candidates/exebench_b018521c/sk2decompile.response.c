void cpuid(unsigned int op, unsigned int *eax, unsigned int *ebx,
           unsigned int *ecx, unsigned int *edx) {
  unsigned int a, b, c, d;
  __asm__ __volatile__(
      "cpuid"
      : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
      : "a"(op));
  *eax = a;
  *ebx = b;
  *ecx = c;
  *edx = d;
}