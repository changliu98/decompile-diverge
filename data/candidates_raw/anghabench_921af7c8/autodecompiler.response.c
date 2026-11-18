__attribute__((used)) static unsigned short addr_to_buddy(unsigned long addr)
{
	addr &= ~PAGE_MASK;
	addr >>= BUDDY_SHIFT;
	return addr & 0xffff;
}