int __cdecl prot2perm(int x)
{
  int r; // [rsp+0h] [rbp-8h]

  r = 0;
  if ( (x & 1) != 0 )
    r = 4;
  if ( (x & 2) != 0 )
    r |= 2u;
  if ( (x & 4) != 0 )
    return r | 1;
  return r;
}