void __cdecl f(int *a, int *b)
{
  int v2; // ecx

  if ( *a <= *b )
  {
    *a *= 2;
    v2 = *b / 2;
  }
  else
  {
    *a /= 2;
    v2 = 2 * *b;
  }
  *b = v2;
}