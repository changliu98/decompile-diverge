unsigned __int64 __cdecl adjust_stack_addr(unsigned __int64 addr, unsigned int n)
{
  return 8LL * n + addr;
}