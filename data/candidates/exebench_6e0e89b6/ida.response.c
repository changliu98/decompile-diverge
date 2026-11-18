void __cdecl clear_bit(int nr, unsigned __int64 *addr)
{
  addr[(unsigned __int64)nr >> 6] &= ~(1LL << (nr & 0x3F));
}