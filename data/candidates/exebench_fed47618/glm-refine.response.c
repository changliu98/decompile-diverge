int __cdecl atomicDecrement(volatile int *var)
{
  // _InterlockedDecrement performs an atomic decrement on the 32-bit integer 
  // pointed to by 'var' and returns the resulting decremented value.
  // Semantically equivalent to: return --(*var); but guaranteed to be atomic.
  return _InterlockedDecrement(var);
}