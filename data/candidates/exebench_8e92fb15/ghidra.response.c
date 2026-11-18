void cylinder(float r,float h,float *csa,float *tsa,float *vol)

{
  float *vol_local;
  float *tsa_local;
  float *csa_local;
  float h_local;
  float r_local;
  
  *csa = (DAT_0010200c * r * h * DAT_00102008) / DAT_00102004;
  *tsa = (DAT_0010200c * r * (h + r) * DAT_00102008) / DAT_00102004;
  *vol = (r * r * h * DAT_00102008) / DAT_00102004;
  return;
}