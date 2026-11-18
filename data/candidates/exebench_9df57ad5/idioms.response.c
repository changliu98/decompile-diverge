void a_store(int *val, int v)
{
  int tmp = v;
  __asm__ __volatile__ (
    "mov %0, %%eax\n\t"
    "lock; xchgl %1, %%eax\n\t"
    :"=a"(tmp), "=m"(*val)
    :"0"(tmp), "m"(*val)
    :"memory");
}