void
a_inc(struct a *a)
{
	LOCK(a);
	a->i++;
	UNLOCK(a);
}