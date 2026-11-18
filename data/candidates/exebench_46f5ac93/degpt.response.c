// Releases the spin lock by setting the lock variable to 0 (unlocked state).
void spin_unlock(int *lock_ptr)
{
  // Set the lock value to 0 to indicate that the resource is now free.
  *lock_ptr = 0;
}