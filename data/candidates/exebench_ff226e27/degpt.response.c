// Atomically adds the integer value 'i' to the long integer pointed to by 'v'.
// Uses LOCK() to acquire the lock before modifying the value.
// Performs the addition: *(int *)v = (int)*v + i.
// Uses UNLOCK() to release the lock after the modification.
void atomic_add(int value, long *target)
{
  LOCK();
  *(int *)target = (int)*target + value;
  UNLOCK();
}