int __cdecl atomic_add(volatile int *ptr, int incr)
{
  return _InterlockedExchangeAdd(ptr, incr);
}