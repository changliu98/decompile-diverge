void __cdecl af_filter_bilinear(const float *a, const float *b, float *k, float fs, float *coef)
{
  // Precompute common terms for the bilinear transform
  float fs2 = fs * fs;
  float a0 = a[0];
  float a1 = a[1];
  float a2 = a[2];
  float b0 = b[0];
  float b1 = b[1];
  float b2 = b[2];

  // Calculate the denominator terms for the analog prototype
  // ad = a0 + 2*a1*fs + 4*a2*fs^2
  float ad = a0 + 2.0f * a1 * fs + 4.0f * a2 * fs2;
  
  // bd = b0 + 2*b1*fs + 4*b2*fs^2
  float bd = b0 + 2.0f * b1 * fs + 4.0f * b2 * fs2;

  // Apply the overall gain factor to the existing gain 'k'
  *k *= ad / bd;

  // Calculate the digital filter coefficients (standard biquad structure)
  // coef[0] = (2*b0 - 8*b2*fs^2) / bd
  *coef = (2.0f * b0 - 8.0f * b2 * fs2) / bd;
  
  // coef[1] = (4*b2*fs^2 - 2*b1*fs + b0) / bd
  coef[1] = (4.0f * b2 * fs2 - 2.0f * b1 * fs + b0) / bd;
  
  // coef[2] = (2*a0 - 8*a2*fs^2) / ad
  coef[2] = (2.0f * a0 - 8.0f * a2 * fs2) / ad;
  
  // coef[3] = (4*a2*fs^2 - 2*a1*fs + a0) / ad
  coef[3] = (4.0f * a2 * fs2 - 2.0f * a1 * fs + a0) / ad;
}