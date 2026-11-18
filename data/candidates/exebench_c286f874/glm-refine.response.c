int __cdecl fetch_and_add(int *p, int i)
{
  // _InterlockedExchangeAdd atomically adds 'i' to '*p' and returns the previous value of '*p'.
  return _InterlockedExchangeAdd(p, i);
}