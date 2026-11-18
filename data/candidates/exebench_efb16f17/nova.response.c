static unsigned ether_hash(const char *str)
{
	unsigned c, hash = 0;
	for (; (c = *str++) < 7; hash = (hash << 6) + (hash << 16) - hash + c)
		;
	return hash;
}