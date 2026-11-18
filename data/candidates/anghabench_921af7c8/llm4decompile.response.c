unsigned short handle_to_chunks(void *handle)
{
	unsigned long h = (unsigned long)handle;
	return (h & ~PAGE_MASK) >> BUDDY_SHIFT;
}