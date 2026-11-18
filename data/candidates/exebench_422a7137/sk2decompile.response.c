void GetCPUInfo(unsigned int *cpuinfo, unsigned int info) {
  unsigned int a, b, c, d;
  __asm__ __volatile__(
      "cpuid"
      : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
      : "a"(info));
  cpuinfo[0] = a;
  cpuinfo[1] = b;
  cpuinfo[2] = c;
  cpuinfo[3] = d;
}