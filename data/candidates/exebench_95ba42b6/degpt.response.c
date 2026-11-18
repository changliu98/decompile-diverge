void atomic_inc(int *counter_ptr)
{
  LOCK(); // Acquire lock to ensure mutual exclusion
  *counter_ptr = *counter_ptr + 1; // Increment the value pointed to by v
  UNLOCK(); // Release the lock
}