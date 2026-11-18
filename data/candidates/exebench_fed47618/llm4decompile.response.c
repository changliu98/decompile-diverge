int atomicDecrement(ATOMIC *v)
{
	int value;

	LOCK();
	value = --(*v);
	UNLOCK();
	return (value);
}