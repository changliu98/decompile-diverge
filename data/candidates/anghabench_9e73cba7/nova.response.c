static inline int uasm_in_compat_space_p(long x)
{
	return (x & 0x00ffffff) == x;
}