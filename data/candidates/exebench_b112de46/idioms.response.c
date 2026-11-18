void af_filter_bilinear(float *ss, float *ss2, float fs, float *k, float *coef)
{
  float a; float b;
  a = ss[0]+2.0*ss[1]*fs+4.0*ss[2]*fs*fs;
  b = ss2[0]+2.0*ss2[1]*fs+4.0*ss2[2]*fs*fs;
  k[0] *= a/b;
  coef[0] = (ss2[0]+2.0*ss2[1]*fs-8.0*ss2[2]*fs*fs)/b;
  coef[1] = (ss2[0]-2.0*ss2[1]*fs+4.0*ss2[2]*fs*fs)/b;
  coef[2] = (ss[0]+2.0*ss[1]*fs-8.0*ss[2]*fs*fs)/a;
  coef[3] = (ss[0]-2.0*ss[1]*fs+4.0*ss[2]*fs*fs)/a;
}