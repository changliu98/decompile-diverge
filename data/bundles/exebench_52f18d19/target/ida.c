int __cdecl atomicIncrement(volatile int *var)
{
  return _InterlockedIncrement(var);
}