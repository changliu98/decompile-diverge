void cpuid_detect(int *has_sse, int *has_sse2) {
  int regs[4];
  regs[0] = 1;
  __asm__("cpuid"
          : "=a"(regs[0]), "=b"(regs[1]), "=c"(regs[2]), "=d"(regs[3])
          : "a"(regs[0]));
  if (has_sse) *has_sse = (regs[3] >> 26) & 1;
  if (has_sse2) *has_sse2 = regs[2] & 1;
}