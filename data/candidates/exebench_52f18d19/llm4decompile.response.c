int atomicIncrement(ATOMIC *v)
{
	int value;

	LOCK();
	value = ++(*v);
	UNLOCK();
	return value;
}