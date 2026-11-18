void nvgTransformTranslate(float *t,float tx,float ty)

{
  float ty_local;
  float tx_local;
  float *t_local;
  
  *t = DAT_00102004;
  t[1] = 0.0;
  t[2] = 0.0;
  t[3] = DAT_00102004;
  t[4] = tx;
  t[5] = ty;
  return;
}