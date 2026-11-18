void spin_unlock(struct lock *lock)
{
  lock->lock = 0;
}