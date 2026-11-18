// Atomically adds 'incr' to the integer value pointed to by 'ptr'
// and returns the original value before the addition.
// Uses LOCK/UNLOCK to ensure thread safety.
int atomic_add(int *target_value, int increment)
{
    LOCK(); // Acquire lock to prevent concurrent access
    int previous_value = *target_value; // Read the current value
    *target_value += increment; // Update the value by adding 'incr'
    UNLOCK(); // Release lock
    return previous_value; // Return the original value
}