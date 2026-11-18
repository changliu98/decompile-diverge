void __cdecl fft2pt(float *ioptr)
{
  // Load the two complex numbers (A and B) from memory
  // A = ioptr[0] (real) + i*ioptr[1] (imag)
  // B = ioptr[2] (real) + i*ioptr[3] (imag)
  float a_real = ioptr[0];
  float a_imag = ioptr[1];
  float b_real = ioptr[2];
  float b_imag = ioptr[3];

  // Perform 2-point Discrete Fourier Transform (DFT) butterfly operation
  // X[0] = A + B
  ioptr[0] = a_real + b_real;
  ioptr[1] = a_imag + b_imag;

  // X[1] = A - B
  ioptr[2] = a_real - b_real;
  ioptr[3] = a_imag - b_imag;
}