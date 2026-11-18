const char *__cdecl func0(int a, int b, int c)
{
  if ( b * b - c * 4 * a > 0 )
    return "2 solutions";
  if ( b * b == c * 4 * a )
    return "1 solution";
  return "No solutions";
}