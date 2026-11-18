void __cdecl generic_set_bit(int nr, volatile unsigned __int64 *addr)
{
  addr[nr / 32] |= 1LL << (nr % 32);
}