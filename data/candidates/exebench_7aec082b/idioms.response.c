int g(int *a, short *b)
{
  int c = *b;
  *a = 10;
  return c;
}