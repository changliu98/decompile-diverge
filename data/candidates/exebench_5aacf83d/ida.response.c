int __cdecl a_swap(volatile int *p, int v)
{
  return _InterlockedExchange(p, v);
}