int __cdecl func0(int x, int y)
{
  int z; // [rsp+0h] [rbp-Ch]

  if ( x <= y )
    z = y;
  else
    z = x;
  while ( z % x || z % y )
    ++z;
  return z;
}