int __cdecl CalcOffsetAndShift(const int x, const int y, size_t *offset, size_t *shift)
{
  if ( (unsigned int)x > 0x53 || (unsigned int)y >= 0x30 )
    return -1;
  if ( !offset || !shift )
    return -1;
  *offset = 84 * (y / 8) + x;
  *shift = y % 8;
  return 0;
}