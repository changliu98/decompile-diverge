void __cdecl makeipt(int nw, int *ip_0)
{
  int p; // [rsp+4h] [rbp-24h]
  int m2; // [rsp+8h] [rbp-20h]
  int m; // [rsp+Ch] [rbp-1Ch]
  int j; // [rsp+14h] [rbp-14h]

  ip_0[2] = 0;
  ip_0[3] = 16;
  m = 2;
  while ( nw > 32 )
  {
    m2 = 2 * m;
    for ( j = m; j < m2; ++j )
    {
      p = 4 * ip_0[j];
      ip_0[j + m] = p;
      ip_0[j + m2] = 16 * m + p;
    }
    m *= 2;
    nw >>= 2;
  }
}