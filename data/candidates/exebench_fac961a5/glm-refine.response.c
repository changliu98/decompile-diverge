void __cdecl rfft1pt(float *ioptr)
{
  // Load the real and imaginary components from memory
  float real = ioptr[0];
  float imag = ioptr[1];

  // Compute the new imaginary part (difference)
  float new_imag = real - imag;

  // Compute the new real part (sum) and store it
  ioptr[0] = real + imag;

  // Store the new imaginary part
  ioptr[1] = new_imag;
}