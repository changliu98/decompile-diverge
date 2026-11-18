__attribute__((used)) static unsigned int walNextHash(unsigned int h)
{
	return (h + 1) & (HASHTABLE_NSLOT - 1);
}