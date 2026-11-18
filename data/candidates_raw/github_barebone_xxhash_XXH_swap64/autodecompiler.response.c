unsigned long long swap64(unsigned long long x)
{
    return
	(x>>56) |
	((x>>40) & 0xffUL) |
	((x>>24) & 0xffUL) |
	((x>>8)  & 0xffUL) |
	((x<<8)  & 0xff00UL) |
	((x<<24) & 0xff0000UL) |
	((x<<40) & 0xff000000UL) |
	(x<<56);
}