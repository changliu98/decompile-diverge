void fancySwap(int *a, int *b)
{
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}