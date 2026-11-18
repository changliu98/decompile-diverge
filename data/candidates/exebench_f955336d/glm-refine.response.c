int __cdecl a_fetch_add(volatile int *x, int v)
{
  // _InterlockedExchangeAdd performs an atomic fetch-and-add.
  // It returns the original value of *x before the addition.
  return _InterlockedExchangeAdd(x, v);
}