void spin_init(struct spin *lock)
{
  lock->lock = 0;
}