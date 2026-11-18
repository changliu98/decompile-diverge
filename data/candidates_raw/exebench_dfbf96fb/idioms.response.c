int atomic_int_get_and_set(int *target, int newval)
{
  int oldval;
  __asm__ __volatile__ (
  "1:\tll %0, %2\n\t"
  "   sc %1, %2\n\t"
  "   jne 1b"
  :"=r"(oldval), "=m"(*target)
  :"m"(*target), "0"(newval)
  );
  return oldval;
}