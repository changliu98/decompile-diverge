int __cdecl decToBin(int n, int *binary)
{
  int y; // [rsp+0h] [rbp-1Ch]
  unsigned int x; // [rsp+4h] [rbp-18h]
  int xa; // [rsp+4h] [rbp-18h]
  unsigned int i; // [rsp+8h] [rbp-14h]
  unsigned int ia; // [rsp+8h] [rbp-14h]
  int na; // [rsp+18h] [rbp-4h]

  na = n;
  i = 1;
  x = 0;
  while ( i <= n )
  {
    i *= 2;
    ++x;
  }
  ia = i >> 1;
  xa = x - 1;
  for ( y = xa; y >= 0; --y )
  {
    if ( (int)(na - ia) < 0 )
    {
      binary[xa - y] = 0;
    }
    else
    {
      na -= ia;
      binary[xa - y] = 1;
    }
    ia >>= 1;
  }
  return xa;
}