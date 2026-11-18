void __cdecl increment(unsigned int *n)
{
  unsigned int w; // [rsp+0h] [rbp-10h]
  unsigned int x; // [rsp+4h] [rbp-Ch]

  x = *n;
  for ( w = 1; (w & x) != 0; w *= 2 )
    x ^= w;
  *n = w ^ x;
}