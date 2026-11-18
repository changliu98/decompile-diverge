void cpuid_count(int op, int count, int *eax, int *ebx, int *ecx, int *edx)
{
  int a; int b; int c; int d;
  __asm__ __volatile__ (
  "cpuid"
  :"=a"(a), "=b"(b), "=c"(c), "=d"(d)
  :"0"(op), "2"(count));
  *eax = a;
  *ebx = b;
  *ecx = c;
  *edx = d;
}