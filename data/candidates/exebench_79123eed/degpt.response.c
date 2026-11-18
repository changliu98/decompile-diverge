void quant_u_dec(int index,float *p_data,float qmin,float qmax,int nlev)

{
  float step;
  int nlev_local;
  float qmax_local;
  float qmin_local;
  float *p_data_local;
  int index_local;
  
  *p_data = (float)index * ((qmax - qmin) / (float)(nlev + -1)) + qmin;
  return;
}