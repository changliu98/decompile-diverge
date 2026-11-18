int twiddle1(int *a, int *b)
{
  *a += *b;
  *a += *b;
  return *a;
}