int __cdecl hclib_atomic_dec_release(volatile int *target)
{
  // _InterlockedDecrement performs an atomic decrement and acts as a full memory barrier.
  // The "release" suffix in the function name implies release semantics, which are satisfied 
  // (and strictly superseded) by the full barrier of the interlocked intrinsic.
  return _InterlockedDecrement(target);
}