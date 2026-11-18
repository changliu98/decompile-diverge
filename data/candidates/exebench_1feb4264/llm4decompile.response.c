int
atomicCompareAndSwap(int *target, int oldValue, int newValue)
{
	int actualOldValue;

	LOCK();
	if (*target == oldValue) {
		*target = newValue;
		actualOldValue = oldValue;
	} else {
		actualOldValue = *target;
	}
	UNLOCK();

	return actualOldValue;
}