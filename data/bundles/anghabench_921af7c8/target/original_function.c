unsigned short handle_to_chunks(unsigned long handle)
{
	return (handle & ~PAGE_MASK) >> BUDDY_SHIFT;
}