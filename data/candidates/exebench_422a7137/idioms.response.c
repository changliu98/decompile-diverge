void GetCPUInfo(int *info, int info_type)
{
  int a; int b; int c; int d;
  __asm__ __volatile__ (
    "cpuid"
    :"=a"(a), "=b"(b), "=c"(c), "=d"(d)
    :"0"(info_type)
  );
  info[0] = a;
  info[1] = b;
  info[2] = c;
  info[3] = d;
}