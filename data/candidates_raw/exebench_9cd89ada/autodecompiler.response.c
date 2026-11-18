void
_thr_spinlock_lock(struct spinlock *lck)
{
	lck->locked = 0;
}