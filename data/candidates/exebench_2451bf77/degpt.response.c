// Releases the spin lock by setting the lock variable to 0.
void spin_unlock(int *lock_ptr)
{
  // Set the lock to unlocked state
  *lock_ptr = 0;
}