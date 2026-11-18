int log2i(unsigned long x)
{
  int i = 0;
  while ((1ul << i) < x)
    ++i;
  return i;
}