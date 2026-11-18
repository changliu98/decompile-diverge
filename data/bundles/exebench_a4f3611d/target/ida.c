int __cdecl sync_test_and_change_bit(int nr, volatile unsigned __int64 *addr)
{
  _RAX = addr;
  _ECX = nr;
  __asm { lock btc [rax], ecx }
  return -_CF;
}