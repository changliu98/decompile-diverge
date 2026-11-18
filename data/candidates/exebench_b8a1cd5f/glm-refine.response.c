int __cdecl atomic32_decrement(int *dest)
{
  // _InterlockedDecrement performs an atomic decrement of the 32-bit integer 
  // pointed to by 'dest' and returns the resulting decremented value.
  // Semantically equivalent to: return --(*dest); but guaranteed to be atomic.
  return _InterlockedDecrement(dest);
}