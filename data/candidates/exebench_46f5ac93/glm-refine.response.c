void __cdecl spin_unlock(volatile int *lock)
{
  *(volatile unsigned char *)lock = 0;
}