int uasm_in_compat_space_p(long addr)
{
	/* Is this address in 32bit compat space? */
	return addr == (int)addr;
}