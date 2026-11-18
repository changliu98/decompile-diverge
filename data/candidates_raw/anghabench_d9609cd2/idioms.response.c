int bcd2bin(int bcd)
{
  int bin = 0;
  int mask = 0;
  int shift = 0;
  mask = 0x0f;
  shift = 0;
  bin = (bcd & mask) << shift;
  mask = 0x70;
  shift = 4;
  bin |= (bcd & mask) << shift;
  mask = 0x1c0;
  shift = 7;
  bin |= (bcd & mask) << shift;
  mask = 0xe000;
  shift = 14;
  bin |= (bcd & mask) >> shift;
  mask = 0x100000;
  shift = 20;
  bin |= (bcd & mask) >> shift;
  return bin;
}