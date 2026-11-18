int ilog2(int x)
{
  return (int)(log2((double)(-(x & (unsigned int)(x)) )) + 1);
}