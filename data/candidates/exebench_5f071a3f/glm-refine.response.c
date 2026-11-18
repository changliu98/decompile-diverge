void __cdecl StoreUintptr(uintptr_t *addr, uintptr_t val)
{
  uintptr_t expected;

  // Atomically stores `val` into `addr` using a Compare-And-Swap (CAS) loop.
  // This is a standard lock-free implementation of an atomic store.
  for (expected = *addr; 
       _InterlockedCompareExchange64((volatile signed __int64 *)addr, val, expected) != expected; 
       expected = *addr)
  {
    // Retry until the CAS operation succeeds.
  }
}