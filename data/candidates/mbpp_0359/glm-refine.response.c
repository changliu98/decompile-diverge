const char *__cdecl func0(int a, int b, int c)
{
  // Checks if the point (a, b) lies on the parabola y^2 = 9 * a * c
  // or equivalently if 2 * b^2 == 9 * a * c
  if ( 2 * b * b == 9 * a * c )
    return "true"; // &unk_2004
  else
    return "false"; // &unk_2008
}