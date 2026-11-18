int __cdecl plot_digit_wierd(char digit, float row, float col, float hgt, float h, float *vx, float *vy)
{
  int num; // [rsp+0h] [rbp-50h]
  int numa; // [rsp+0h] [rbp-50h]
  int ie; // [rsp+Ch] [rbp-44h]
  int ib; // [rsp+10h] [rbp-40h]
  int i; // [rsp+14h] [rbp-3Ch]
  float he; // [rsp+18h] [rbp-38h]
  float hl; // [rsp+1Ch] [rbp-34h]
  float cs_0; // [rsp+20h] [rbp-30h]
  float rs; // [rsp+24h] [rbp-2Ch]

  num = 0;
  if ( digit < 48 || digit > 57 )
    return 0;
  ib = plot_digit_wierd_lt[digit - 47];
  ie = plot_digit_wierd_lt[digit - 46] - 1;
  for ( i = ib; i <= ie; ++i )
  {
    hl = hgt * (float)(plot_digit_wierd_lb[i] / 10);
    he = h * (float)(plot_digit_wierd_lb[i] % 10);
    if ( i != ib )
    {
      vx[num] = rs;
      vy[num] = cs_0;
      numa = num + 1;
      vx[numa] = row - hl;
      vy[numa] = col - he;
      num = numa + 1;
    }
    rs = row - hl;
    cs_0 = col - he;
  }
  return num;
}