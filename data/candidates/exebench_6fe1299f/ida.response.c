void __cdecl quant_u(float *p_data, int *p_index, float qmin, float qmax, int nlev)
{
  float v5; // xmm0_4
  float qbnd; // [rsp+Ch] [rbp-2Ch]
  float step; // [rsp+10h] [rbp-28h]
  int i; // [rsp+18h] [rbp-20h]

  step = (float)(qmax - qmin) / (float)(nlev - 1);
  v5 = step * 0.5 + qmin;
  qbnd = v5;
  for ( i = 0; i < nlev - 1 && qbnd <= *p_data; ++i )
    qbnd = step + qbnd;
  *p_data = (float)((float)i * step) + qmin;
  *p_index = i;
}