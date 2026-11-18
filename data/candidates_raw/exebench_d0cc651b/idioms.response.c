static void f1(unsigned int *a)
{
  unsigned int x = *a;
  unsigned int w = 1;
  while (x & w)
    w <<= 1;
  w ^= x;
  *a = w ^ x;
}