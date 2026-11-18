static inline void do_cpuid(unsigned int *eax, unsigned int *ebx,
                            unsigned int *ecx, unsigned int *edx) {
  unsigned int a, b, c, d;
  a = *eax;
  __asm__ __volatile__("cpuid"
                       : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
                       : "0"(a), "2"(c));
  *eax = a;
  *ebx = b;
  *ecx = c;
  *edx = d;
}