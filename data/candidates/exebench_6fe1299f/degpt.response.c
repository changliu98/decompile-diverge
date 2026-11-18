void quant_u(float *p_data,int *p_index,float qmin,float qmax,int nlev)

{
  float fVar1;
  float *p_in;
  float qbnd;
  float step;
  int j;
  int i;
  int nlev_local;
  float qmax_local;
  float qmin_local;
  int *p_index_local;
  float *p_data_local;
  
  fVar1 = (qmax - qmin) / (float)(nlev + -1);
  i = 0;
  for (qbnd = (float)((double)fVar1 * DAT_00102008 + (double)qmin);
      (i < nlev + -1 && (qbnd <= *p_data)); qbnd = fVar1 + qbnd) {
    i = i + 1;
  }
  *p_data = (float)i * fVar1 + qmin;
  *p_index = i;
  return;
}