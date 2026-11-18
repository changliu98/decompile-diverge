int
all_bits_clear(unsigned test, unsigned mask)
{
	return (test & mask) == 0;
}