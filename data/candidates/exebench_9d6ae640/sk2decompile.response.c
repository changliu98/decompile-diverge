void cpuinfo(int info, int *eax, int *ebx, int *ecx, int *edx) {
  int a, b, c, d;
  __asm__("cpuid"
          : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
          : "a"(info));
  *eax = a;
  *ebx = b;
  *ecx = c;
  *edx = d;
}