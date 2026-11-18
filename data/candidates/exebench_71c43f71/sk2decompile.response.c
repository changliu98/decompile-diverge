void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx,
                  unsigned int *edx) {
  unsigned int a, b, c, d;
  a = *eax;
  __asm__("cpuid"
          : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
          : "a"(a), "c"(0));
  *eax = a;
  *ebx = b;
  *ecx = c;
  *edx = d;
}