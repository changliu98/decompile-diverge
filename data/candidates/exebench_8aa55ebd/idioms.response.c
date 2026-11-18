static void run_cpuid(int function, int subfunction, int *data)
{
  __asm__ __volatile__ (
    "cpuid"
    :"=a" (data[0]), "=b" (data[1]), "=c" (data[2]), "=d" (data[3])
    :"0" (function), "2" (subfunction));
}