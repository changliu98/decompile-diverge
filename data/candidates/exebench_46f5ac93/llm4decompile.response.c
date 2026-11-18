void spin_unlock(struct spinlock *lock)
{
 lock->locked = 0;
}