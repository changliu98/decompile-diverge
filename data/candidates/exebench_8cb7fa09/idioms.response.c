static void cpuid(int op, int *eax, int *ebx, int *ecx, int *edx)
{
  int a; int b; int c; int d;
  __asm__ __volatile__ (
    "cpuid"
    :"=a"(a), "=b"(b), "=c"(c), "=d"(d)
    :"0"(op)
    );
  *eax = a;
  *ebx = b;
  *ecx = c;
  *edx = d;
}