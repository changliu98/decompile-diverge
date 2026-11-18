void dpaa_clear_bits(unsigned long mask, unsigned long *p)
{
	*p &= ~mask;
}