int __cdecl atomic_sub(volatile int *i, int j)
{
  return _InterlockedExchangeAdd(i, -j);
}