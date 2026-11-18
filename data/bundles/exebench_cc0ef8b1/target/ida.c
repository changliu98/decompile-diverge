float __cdecl xCorrCoef(float *target, float *regressor, int subl)
{
  float ftmp2; // [rsp+0h] [rbp-28h]
  float ftmp1; // [rsp+4h] [rbp-24h]
  int i; // [rsp+8h] [rbp-20h]

  ftmp1 = 0.0;
  ftmp2 = 0.0;
  for ( i = 0; i < subl; ++i )
  {
    ftmp1 = (float)(target[i] * regressor[i]) + ftmp1;
    ftmp2 = (float)(regressor[i] * regressor[i]) + ftmp2;
  }
  if ( ftmp1 <= 0.0 )
    return 0.0;
  else
    return (float)(ftmp1 * ftmp1) / ftmp2;
}