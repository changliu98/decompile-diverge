void __cdecl spin_unlock(volatile int *p)
{
  *p = 0;
}