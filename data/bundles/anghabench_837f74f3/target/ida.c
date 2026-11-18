void __cdecl set_bit(uint8_t *data, size_t pos)
{
  data[pos >> 3] |= 1 << (7 - (pos & 7));
}