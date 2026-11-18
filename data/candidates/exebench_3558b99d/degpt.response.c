long ff_atomic_dec_long(long *counter)
{
  long previous_value;
  
  // Acquire lock to ensure atomicity
  LOCK();
  // Read the current value before decrementing
  previous_value = *counter;
  // Decrement the value in place
  *counter = *counter - 1;
  // Release the lock
  UNLOCK();
  // Return the decremented value
  return previous_value - 1;
}