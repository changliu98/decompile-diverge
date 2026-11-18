// Atomically decrements the value pointed to by 'target' using a relaxed memory order.
// Acquires a lock to ensure thread safety, reads the current value,
// decrements it, stores the new value, and returns the decremented result.
int _hclib_atomic_dec_relaxed(int *ptr)
{
    LOCK(); // Acquire lock to ensure mutual exclusion
    int current_value = *ptr; // Read the current value of the target
    *ptr = current_value - 1; // Decrement the value and store it back
    UNLOCK(); // Release the lock
    return current_value - 1; // Return the new decremented value
}