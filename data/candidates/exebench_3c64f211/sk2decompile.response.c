void jpq_cpuid_custom(unsigned int* regs, unsigned int code) {
  unsigned int eax, ebx, ecx, edx;
  __asm__ __volatile__(
      "cpuid"
      : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
      : "a"(code));
  regs[0] = eax;
  regs[1] = ebx;
  regs[2] = ecx;
  regs[3] = edx;
}