int __cdecl func0(int x, int y)
{
  if ( y < 0 )
    return -func0(x, -y);
  if ( !y )
    return 0;
  if ( y == 1 )
    return x;
  return func0(x, y - 1) + x;
}