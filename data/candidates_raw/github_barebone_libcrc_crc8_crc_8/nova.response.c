static unsigned char func0(const unsigned char *name, size_t len)
{
	unsigned char hash = 0;
	size_t i = 0;

	if (name) {
		while (i < len) {
			hash = table[hash ^ *name++];
			i++;
		}
	}
	return hash;
}