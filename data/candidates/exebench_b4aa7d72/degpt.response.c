void grad1(int hash,float *gx)

{
  int h;
  float *gx_local;
  int hash_local;
  
  *gx = DAT_00102004 + (float)(hash & 7);
  if ((hash & 8U) != 0) {
    *gx = -*gx;
  }
  return;
}