void __cdecl UNLOCK(int *f)
{
  if ( _InterlockedExchangeAdd(f, 0xFFFFFFFF) == 2 )
  {
    _InterlockedExchange(f, 0);
    syscall(202LL, f, 1LL);
  }
}