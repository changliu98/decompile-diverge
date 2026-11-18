void __cdecl rifft1pt(float *ioptr, float scale)
{
  // Extract the real and imaginary parts of the complex input
  float real = ioptr[0];
  float imag = ioptr[1];

  // Compute the new imaginary part: (real - imag) * scale
  float new_imag = scale * (real - imag);

  // Compute the new real part: (real + imag) * scale
  float new_real = scale * (real + imag);

  // Store the results back into the memory buffer
  ioptr[0] = new_real;
  ioptr[1] = new_imag;
}