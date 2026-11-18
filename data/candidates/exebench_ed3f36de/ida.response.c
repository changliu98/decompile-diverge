void __cdecl test_mean2(double *xymean, double *xy, int n)
{
  double ysum; // [rsp+0h] [rbp-28h]
  double xsum; // [rsp+8h] [rbp-20h]
  int i; // [rsp+10h] [rbp-18h]
  int ia; // [rsp+10h] [rbp-18h]

  xsum = 0.0;
  ysum = 0.0;
  for ( i = 0; i < 2 * n; i += 2 )
    xsum = xy[i] + xsum;
  for ( ia = 0; ia < 2 * n; ia += 2 )
    ysum = xy[ia + 1] + ysum;
  *xymean = xsum / (double)n;
  xymean[1] = ysum / (double)n;
}