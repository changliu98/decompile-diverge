// Atomically increments the integer value pointed to by p
void a_inc(int *target_value)
{
  LOCK(); // Acquire lock to ensure thread-safe access
  *target_value = *target_value + 1; // Increment the value at the memory location pointed to by p
  UNLOCK(); // Release lock to allow other threads to access the resource
}