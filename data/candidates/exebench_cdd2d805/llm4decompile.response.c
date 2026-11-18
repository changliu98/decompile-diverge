void
atomic_retain(struct atomic *a)
{
	LOCK(a);
	a->count++;
	UNLOCK(a);
}