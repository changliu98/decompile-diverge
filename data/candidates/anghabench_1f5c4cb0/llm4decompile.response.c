size_t
__reverse_ffs (unsigned long word)
{
  int num = 0;

  if ((word & 0xffff0000) == 0)
    {
      num += 16;
      word <<= 16;
    }

  if ((word & 0xff00) == 0)
    {
      num += 8;
      word <<= 8;
    }

  if ((word & 0xf0) == 0)
    {
      num += 4;
      word <<= 4;
    }

  if ((word & 0x0c) == 0)
    {
      num += 2;
      word <<= 2;
    }

  if ((word & 0x02) == 0)
    {
      num += 1;
      word <<= 1;
    }

  return num;
}