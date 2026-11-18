__attribute__((used)) static unsigned int advance_hash(unsigned int h)
{
	return (h + 1) & (HASHTABLE_NSLOT - 1);
}