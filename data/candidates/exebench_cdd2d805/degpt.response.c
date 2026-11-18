// Atomically increments the integer value pointed to by p
// Uses LOCK/UNLOCK to ensure thread-safe increment operation
void atomic_retain(int *value_ptr)
{
  LOCK();
  *value_ptr = *value_ptr + 1;
  UNLOCK();
}