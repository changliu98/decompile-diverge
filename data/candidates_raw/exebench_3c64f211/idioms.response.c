static void cpuid(int *result, int InfoType)
{
  int i;
  __asm__ __volatile__ (
  "cpuid"
  :"=a"(result[0]), "=b"(result[1]), "=c"(result[2]), "=d"(result[3])
  :"0"(InfoType)
  );
}