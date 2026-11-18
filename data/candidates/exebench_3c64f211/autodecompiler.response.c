void jpq_cpuid_custom(unsigned int cpuinfo[4], unsigned int level)
{
 asm volatile (
  "cpuid"
  : "=a"(cpuinfo[0]), "=b"(cpuinfo[1]), "=c"(cpuinfo[2]), "=d"(cpuinfo[3])
  : "0"(level), "2"(0)
 );
}