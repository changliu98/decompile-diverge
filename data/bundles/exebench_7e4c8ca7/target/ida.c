void __cdecl change_bit(int nr, volatile unsigned __int64 *addr)
{
  addr[nr / 64] ^= 1LL << (nr % 64);
}