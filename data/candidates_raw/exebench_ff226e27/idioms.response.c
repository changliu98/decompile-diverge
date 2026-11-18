void atomic_add(int i, int *v)
{
  __asm__ __volatile__ (
    "lock ; " "incl %0":"+m"(*v) : "cc", "memory"
  );
}