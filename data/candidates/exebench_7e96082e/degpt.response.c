// Atomically decrement the integer value pointed to by v
void atomic_dec(int *value_ptr)
{
  // Acquire lock to ensure exclusive access to the shared variable
  LOCK();
  // Decrement the value by 1
  *value_ptr -= 1;
  // Release the lock to allow other threads to access the shared variable
  UNLOCK();
}