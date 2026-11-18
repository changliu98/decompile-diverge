void __cdecl bitfield_set(unsigned __int64 *bits, int bit)
{
  bits[(unsigned __int64)bit >> 6] |= 1LL << (bit & 0x3F);
}