static void af_filter_bilinear(const float* a, const float* b, float* k,
                               float fs, float *coef)
{
  float ad, bd;


  ad = 4. * a[2] * fs * fs + 2. * a[1] * fs + a[0];

  bd = 4. * b[2] * fs * fs + 2. * b[1] * fs + b[0];


  *k *= ad/bd;


  *coef++ = (2. * b[0] - 8. * b[2] * fs * fs)/bd;
  *coef++ = (4. * b[2] * fs * fs - 2. * b[1] * fs + b[0])/bd;


  *coef++ = (2. * a[0] - 8. * a[2] * fs * fs)/ad;
  *coef = (4. * a[2] * fs * fs - 2. * a[1] * fs + a[0])/ad;
}