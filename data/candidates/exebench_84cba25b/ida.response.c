char *__cdecl base91(char *p, int i)
{
  *p = i / 91 + 33;
  p[1] = i % 91 + 33;
  return p + 2;
}