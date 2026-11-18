int __cdecl trylock(volatile int *lock)
{
  char old_value = *(volatile char *)lock;
  *(volatile char *)lock = 1;
  return old_value == 0;
}