int atmc_fetch_and_add(atmc *ptr, int value)
{
	int prev;

	LOCK();
	prev = *ptr;
	*ptr += value;
	UNLOCK();

	return prev + value;
}