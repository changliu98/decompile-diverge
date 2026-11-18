unsigned long adjust_stack_addr(unsigned long addr, int n)
{
	return addr + n * sizeof(unsigned long);
}