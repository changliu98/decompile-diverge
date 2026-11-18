static inline bool func0(int val, int bit, int *reg)
{
	bool ret;

	bit = ~(1 << bit);
	ret = (val & bit)!= 0;
	*reg &= bit;

	return ret;
}