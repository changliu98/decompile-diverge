double __cdecl func0(int n, int r, double p)
{
  double v4; // [rsp+10h] [rbp-30h]
  int i; // [rsp+1Ch] [rbp-24h]
  double answer; // [rsp+20h] [rbp-20h]
  int ra; // [rsp+38h] [rbp-8h]

  ra = r;
  if ( r > n / 2 )
    ra = n - r;
  answer = 1.0;
  for ( i = 1; i <= ra; ++i )
    answer = (double)(i + n - ra) * answer / (double)i;
  v4 = answer * pow(p, (double)r);
  return v4 * pow(1.0 - p, (double)(n - r));
}