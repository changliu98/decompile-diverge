// Atomically adds delta to the value pointed to by val using a lock.
// Returns the new value (old value + delta) after the addition.
uintptr_t AddUintptr(uintptr_t *target_value, uintptr_t increment)
{
    uintptr_t previous_value;
    LOCK(); // Acquire lock to ensure thread safety
    previous_value = *target_value; // Read the current value
    *target_value += increment; // Update the value by adding delta
    UNLOCK(); // Release the lock
    return previous_value + increment; // Return the new value
}