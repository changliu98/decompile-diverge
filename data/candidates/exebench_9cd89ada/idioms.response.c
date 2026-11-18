void release(struct spin *lock)
{
  lock->lock = 0;
}