int f(int *a, int *b)
{
  *a += *b;
  *a += *b;
  return *a;
}