// Atomically increments the integer value pointed to by 'a'
void atomic_inc(int *counter_ptr)
{
  // Acquire lock to ensure exclusive access to the shared variable
  LOCK();
  // Increment the value at the memory location pointed to by 'a'
  *counter_ptr = *counter_ptr + 1;
  // Release the lock to allow other threads to access the shared variable
  UNLOCK();
}