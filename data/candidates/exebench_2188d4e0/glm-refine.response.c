void __cdecl f(int *a, int *b)
{
  if (*a <= *b)
  {
    *a *= 2;
    *b /= 2;
  }
  else
  {
    *a /= 2;
    *b *= 2;
  }
}