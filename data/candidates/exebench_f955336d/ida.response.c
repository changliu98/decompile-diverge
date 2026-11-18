int __cdecl a_fetch_add(volatile int *x, int v)
{
  return _InterlockedExchangeAdd(x, v);
}