void getCpuid(int *ret, int ax)
{
  int i;
  __asm__ __volatile__(
    "cpuid"
    :"=a"(ret[0]), "=b"(ret[1]), "=c"(ret[2]), "=d"(ret[3])
    :"0"(ax)
  );
}