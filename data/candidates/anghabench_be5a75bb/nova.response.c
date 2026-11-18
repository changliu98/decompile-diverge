static inline int frag_num(int offset)
{
	return 3 - (offset & 0x3);
}