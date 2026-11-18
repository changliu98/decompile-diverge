void convertscreenvertex(float *vec,int resolutionx,int resolutiony)

{
  int iVar1;
  int resolutiony_local;
  int resolutionx_local;
  float *vec_local;
  
  iVar1 = resolutionx >> 1;
  *vec = (*vec - (float)iVar1) / (float)iVar1;
  vec[1] = ((float)(resolutiony >> 1) - vec[1]) / (float)iVar1;
  vec[2] = DAT_00102004;
  return;
}