void __cdecl UNLOCK(int *f)
{
  // _InterlockedExchangeAdd(f, -1) atomically decrements the lock value by 1
  // and returns the previous value.
  if ( _InterlockedExchangeAdd(f, -1) == 2 )
  {
    // If the previous value was 2, it means the lock transitioned from 
    // "locked" (2) to "contended" (1). We must wake up one waiting thread.
    
    // Reset the lock state to "unlocked" (0)
    _InterlockedExchange(f, 0);
    
    // Invoke futex_wake (syscall 202 on x86_64 Linux)
    // Arguments: futex_addr (f), operation (FUTEX_WAKE=1), count (implied 1)
    syscall(202, f, 1);
  }
}