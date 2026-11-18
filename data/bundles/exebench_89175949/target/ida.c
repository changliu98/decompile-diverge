int __cdecl foo(int *a, int *b, int c)
{
  *a *= 2;
  *b /= 2;
  return *b + *a;
}