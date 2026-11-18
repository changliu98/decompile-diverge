void __cdecl spin_unlock(volatile int *lock)
{
  *lock = 0;
}