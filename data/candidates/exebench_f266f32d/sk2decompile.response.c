void getCpuid(unsigned int *cpu, unsigned int function) {
  unsigned int a, b, c, d;
  __asm__ __volatile__(
      "cpuid"
      : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
      : "a"(function));
  cpu[0] = a;
  cpu[1] = b;
  cpu[2] = c;
  cpu[3] = d;
}