int __cdecl foo(int p, int *q)
{
  if ( p == 9 )
    q[1] = 0;
  else
    *q = 0;
  return 3;
}