int
fetch_and_add(int *ptr, int val)
{
	int oldval;

	LOCK();
	oldval = *ptr;
	*ptr += val;
	UNLOCK();
	return (oldval);
}