void run_cpuid(int eax, int ecx, int *ret)
{
  int a = eax; int c = ecx;
  __asm__ __volatile__ (
    "cpuid"
    :"=a"(a), "=b"(ret[1]), "=c"(ret[2]), "=d"(ret[3])
    :"0"(a), "c"(c));
}