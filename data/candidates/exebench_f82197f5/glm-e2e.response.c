void UNLOCK(volatile int *lock) {
    // Atomically subtract 1 from the lock value and return the old value
    int old_val = __atomic_fetch_sub(lock, 1, __ATOMIC_SEQ_CST);
    
    if (old_val == 1) {
        // Fast path: The lock was held exclusively with no waiters.
        // Unlocking is complete, just return.
        return;
    } 
    
    if (old_val == 2) {
        // Slow path: There are waiters (threads blocked on this lock).
        // We must wake one up.
        
        // Atomically set the lock to 0 (unlocked)
        __atomic_store_n(lock, 0, __ATOMIC_SEQ_CST);
        
        // Invoke the futex system call to wake up 1 waiting thread
        // syscall(0xca, lock, 1, 0)
        // 0xca (202) is the syscall number for SYS_futex on x86_64
        // FUTEX_WAKE is 1
        syscall(SYS_futex, lock, 1, 0);
        
        return;
    }
    
    // If old_val is neither 1 nor 2, it falls through to return.
    // (This might indicate an error, such as unlocking an already unlocked lock)
    return;
}