int __cdecl func0(float a, float b, float c)
{
  if ( roundf(a) != a )
    return 0;
  if ( roundf(b) != b )
    return 0;
  if ( roundf(c) == c )
    return (float)(a + b) == c || (float)(a + c) == b || (float)(b + c) == a;
  return 0;
}