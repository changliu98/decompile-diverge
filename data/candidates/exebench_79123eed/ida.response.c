void __cdecl quant_u_dec(int index, float *p_data, float qmin, float qmax, int nlev)
{
  *p_data = (float)((float)index * (float)((float)(qmax - qmin) / (float)(nlev - 1))) + qmin;
}