void __cdecl ifft2pt(float *ioptr, float scale)
{
  // Load inputs (complex numbers: 0 = real, 1 = imag)
  float f0r = ioptr[0];
  float f0i = ioptr[1];
  float f1r = ioptr[2];
  float f1i = ioptr[3];

  // 2-point Inverse FFT butterfly computation
  float sum_r = f0r + f1r;
  float sum_i = f0i + f1i;
  float diff_r = f0r - f1r;
  float diff_i = f0i - f1i;

  // Store scaled outputs
  ioptr[0] = scale * sum_r;
  ioptr[1] = scale * sum_i;
  ioptr[2] = scale * diff_r;
  ioptr[3] = scale * diff_i;
}