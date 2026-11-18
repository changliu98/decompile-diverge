void
release(struct spinlock *lck)
{
	lck->locked = 0;
}