static unsigned int func0(unsigned int secs)
{
	unsigned int val;

	val = (secs + 1) * 8;
	if (val > SLP_RATE_MAX)
		val = SLP_RATE_MAX + 0x10;
	return val;
}