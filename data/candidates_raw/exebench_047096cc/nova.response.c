static void
func0 (unsigned *val)
{
  unsigned byte;

  byte = ((*val) >> 24) & 0xff;
  *val = ((*val) << 8) | ((*val) >> 24);
  *val |= (byte << 24);
}