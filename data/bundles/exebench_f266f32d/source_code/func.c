
static void getCpuid( unsigned int* p, unsigned int ax )
{
  __asm __volatile
  ( "movl %%ebx, %%esi\n\t"
    "cpuid\n\t"
    "xchgl %%ebx, %%esi"
    : "=a" (p[0]), "=S" (p[1]),
      "=c" (p[2]), "=d" (p[3])
    : "0" (ax)
  );
}
