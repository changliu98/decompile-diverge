int __cdecl doit(int *x, int y)
{
  if ( *x <= y )
    return 0;
  *x = y;
  return 1;
}