long __cdecl ff_atomic_dec_long(volatile long *val)
{
  return _InterlockedDecrement64(val);
}