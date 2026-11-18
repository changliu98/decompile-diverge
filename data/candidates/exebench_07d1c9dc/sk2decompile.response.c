void cpuid_count(int count, int function, unsigned int *eax, unsigned int *ebx,
                 unsigned int *ecx, unsigned int *edx) {
  unsigned int a, b, c, d;
  __asm__ __volatile__(
      "cpuid"
      : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
      : "0"(count), "2"(function));
  *eax = a;
  *ebx = b;
  *ecx = c;
  *edx = d;
}