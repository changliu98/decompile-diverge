int __cdecl hclib_atomic_dec_relaxed(volatile int *target)
{
  return _InterlockedDecrement(target);
}