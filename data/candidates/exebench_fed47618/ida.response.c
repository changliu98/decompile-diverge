int __cdecl atomicDecrement(volatile int *var)
{
  return _InterlockedDecrement(var);
}