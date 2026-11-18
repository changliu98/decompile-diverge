void __cdecl h(int *x, int y)
{
  if ( *x <= y )
    *x -= y;
  else
    h(x, *x);
}