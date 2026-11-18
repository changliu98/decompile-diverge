int __cdecl hclib_atomic_dec_release(volatile int *target)
{
  return _InterlockedDecrement(target);
}