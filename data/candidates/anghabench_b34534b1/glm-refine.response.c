char *__cdecl getbase(char *p, int *basep)
{
  if (*p != '0')
  {
    *basep = 10;
    return p;
  }

  switch (p[1])
  {
    case 'n':
    case 't':
      *basep = 10;
      return p + 2;
    case 'o':
      *basep = 8;
      return p + 2;
    case 'x':
      *basep = 16;
      return p + 2;
    default:
      *basep = 10;
      return p;
  }
}