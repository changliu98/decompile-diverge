void __cdecl rfft4pt(float *ioptr)
{
  // Load input data (4 complex numbers: real, imag pairs)
  float f0r = ioptr[0];
  float f0i = ioptr[1];
  float f1r = ioptr[4];
  float f1i = ioptr[5];
  float f2r = ioptr[2];
  float f2i = ioptr[3];
  float f3r = ioptr[6];
  float f3i = ioptr[7];

  // Stage 1: 2-point FFTs (Butterfly 0-1 and 2-3)
  float t0r = f0r + f1r;
  float t0i = f0i + f1i;
  float f1ra = f0r - f1r;
  float f1ia = f0i - f1i;

  float t1r = f2r - f3r;
  float t1i = f2i - f3i;
  float f2ra = f2r + f3r;
  float f2ia = f2i + f3i;

  // Stage 2: Combine the 2-point FFTs
  float f0r_out = t0r + f2ra;
  float f0i_out = t0i + f2ia;
  float f2r_out = t0r - f2ra;
  float f2i_out = f2ia - t0i;

  float f3ra = f1ra - t1i;
  float f3ia = f1ia + t1r;
  float f1rb = f1ra + t1i;
  float f1ib = f1ia - t1r;

  // Stage 3: Final outputs and twiddle factor multiplications
  float t0ra = f0r_out + f0i_out;
  float t0ia = f0r_out - f0i_out;
  float t1ra = f1rb + f3ra;
  float t1ia = f1ib - f3ia;
  float f0ib = f3ra - f1rb;

  // 0.70710677 is sqrt(0.5)
  float f1rc = (0.70710677f * f0ib) + (0.70710677f * (f1ib + f3ia)) + (f1rb + f3ra);
  float f1ic = (0.70710677f * f0ib) - (0.70710677f * (f1ib + f3ia)) + (f1ib - f3ia);

  // Store results back to memory
  ioptr[4] = f2r_out;
  ioptr[5] = f2i_out;
  ioptr[0] = t0ra;
  ioptr[1] = t0ia;
  ioptr[2] = 0.5f * f1rc;
  ioptr[3] = 0.5f * f1ic;
  ioptr[6] = 0.5f * (2.0f * t1ra - f1rc);
  ioptr[7] = 0.5f * (f1ic - 2.0f * t1ia);
}