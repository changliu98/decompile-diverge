static inline u32 func0(u32 val)
{
	u32 ret;

	if (val == 1)
		ret = 1;
	else
		ret = val + 1;

	return ret & 0x3f;
}