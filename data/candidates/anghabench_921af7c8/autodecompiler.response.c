__attribute__((used)) static unsigned short handle_to_chunks(unsigned long addr)
{
	addr &= ~PAGE_MASK;
	addr >>= BUDDY_SHIFT;
	return addr & 0xffff;
}