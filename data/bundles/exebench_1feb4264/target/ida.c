int __cdecl atomicCompareAndSwap(volatile int *var, int ov, int nv)
{
  return _InterlockedCompareExchange(var, nv, ov);
}