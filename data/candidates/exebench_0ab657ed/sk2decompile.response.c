static void run_cpuid(int leaf, int subleaf, int *regs) {
  int eax, ebx, ecx, edx;
  __asm__ __volatile__(
      "cpuid"
      : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
      : "a"(leaf), "c"(subleaf));
  regs[0] = eax;
  regs[1] = ebx;
  regs[2] = ecx;
  regs[3] = edx;
}