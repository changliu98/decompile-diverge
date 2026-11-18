void __cdecl rifft2pt(float *ioptr, float scale)
{
  // Unpack the input complex numbers
  // X0 = ioptr[0] + i*ioptr[1]
  // X1 = ioptr[2] + i*ioptr[3]
  float x0r = ioptr[0];
  float x0i = ioptr[1];
  float x1r = ioptr[2];
  float x1i = ioptr[3];

  // Precompute the twiddle factor multiplication (2.0 * X1)
  float w1r = 2.0 * x1r;
  float w1i = 2.0 * x1i;

  // Compute the intermediate butterfly sums
  // f0r = Re(X0 + X1), f0i = Im(X0 - X1)
  float f0r = x0r + x0i;
  float f0i = x0r - x0i;

  // Apply the final butterfly operations and scale the outputs
  // Y0 = scale * (f0r + w1r)
  // Y1 = scale * (f0i - w1i)
  // Y2 = scale * (f0r - w1r)
  // Y3 = scale * (f0i + w1i)
  ioptr[0] = scale * (float)(f0r + w1r);
  ioptr[1] = scale * (float)(f0i - w1i);
  ioptr[2] = scale * (float)(f0r - w1r);
  ioptr[3] = scale * (float)(f0i + w1i);
}