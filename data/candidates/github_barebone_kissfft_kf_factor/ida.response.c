void __cdecl kf_factor(int n, int *facbuf)
{
  double v2; // xmm0_8
  int *v3; // rax
  double floor_sqrt; // [rsp+10h] [rbp-20h]
  int p; // [rsp+1Ch] [rbp-14h]
  int na; // [rsp+2Ch] [rbp-4h]

  na = n;
  p = 4;
  v2 = sqrt((double)n);
  floor_sqrt = floor(v2);
  do
  {
    while ( na % p )
    {
      if ( p == 2 )
      {
        p = 3;
      }
      else if ( p == 4 )
      {
        p = 2;
      }
      else
      {
        p += 2;
      }
      if ( (double)p > floor_sqrt )
        p = na;
    }
    na /= p;
    *facbuf = p;
    v3 = facbuf + 1;
    facbuf += 2;
    *v3 = na;
  }
  while ( na > 1 );
}