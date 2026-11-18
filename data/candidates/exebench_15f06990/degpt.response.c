// Synchronizes the unlock operation by resetting the pointer value to 0.
void sync_unlock(int *lock_flag)
{
  // Reset the synchronization variable to indicate the lock is released.
  *lock_flag = 0;
}