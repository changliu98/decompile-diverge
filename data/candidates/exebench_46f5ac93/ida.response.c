void __cdecl spin_unlock(volatile int *lock)
{
  *(_BYTE *)lock = 0;
}