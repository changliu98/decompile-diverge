unsigned long long adjust_stack_addr(unsigned long long addr, unsigned int n)
{
    return addr + (8ULL * n);
}