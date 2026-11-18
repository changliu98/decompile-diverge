int __cdecl func0(int n)
{
  if ( !n )
    return 1;
  if ( ((n + 1) & n) != 0 )
    return n | (1 << ((int)(log2((double)((n + 1) & ~n)) + 1.0) - 1));
  return n;
}