int __cdecl xchg(volatile int *addr, int newval)
{
  // _InterlockedExchange atomically writes newval to addr and returns the old value.
  // It acts as a full memory barrier.
  return _InterlockedExchange(addr, newval);
}