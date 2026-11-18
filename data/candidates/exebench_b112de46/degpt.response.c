void af_filter_bilinear(float *a,float *b,float *k,float fs,float *coef)

{
  float fVar1;
  float fVar2;
  float bd;
  float ad;
  float *coef_local;
  float fs_local;
  float *k_local;
  float *b_local;
  float *a_local;
  
  fVar1 = (float)(DAT_00102018 * (double)a[2] * (double)fs * (double)fs +
                  DAT_00102010 * (double)a[1] * (double)fs + (double)*a);
  fVar2 = (float)(DAT_00102018 * (double)b[2] * (double)fs * (double)fs +
                  DAT_00102010 * (double)b[1] * (double)fs + (double)*b);
  *k = (fVar1 / fVar2) * *k;
  *coef = (float)(((double)*b + (double)*b +
                  -(DAT_00102020 * (double)b[2] * (double)fs * (double)fs)) / (double)fVar2);
  coef[1] = (float)((DAT_00102018 * (double)b[2] * (double)fs * (double)fs +
                     -(DAT_00102010 * (double)b[1] * (double)fs) + (double)*b) / (double)fVar2);
  coef[2] = (float)(((double)*a + (double)*a +
                    -(DAT_00102020 * (double)a[2] * (double)fs * (double)fs)) / (double)fVar1);
  coef[3] = (float)((DAT_00102018 * (double)a[2] * (double)fs * (double)fs +
                     -(DAT_00102010 * (double)a[1] * (double)fs) + (double)*a) / (double)fVar1);
  return;
}