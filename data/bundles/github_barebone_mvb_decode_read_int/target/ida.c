int __cdecl read_int(const uint8_t *in, uint32_t *out)
{
  *out = *in & 0x7F;
  if ( *in < 0x80u )
    return 1;
  *out |= (in[1] & 0x7F) << 7;
  if ( in[1] < 0x80u )
    return 2;
  *out |= (in[2] & 0x7F) << 14;
  if ( in[2] < 0x80u )
    return 3;
  *out |= (in[3] & 0x7F) << 21;
  if ( in[3] < 0x80u )
    return 4;
  *out |= (in[4] & 0x7F) << 28;
  return 5;
}