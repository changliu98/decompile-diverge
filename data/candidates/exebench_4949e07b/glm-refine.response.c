void __cdecl cftx020(double *a)
{
  // Treat the array as two complex numbers:
  // z0 = {a[0], a[1]} and z1 = {a[2], a[3]}
  double *z0_real = &a[0];
  double *z0_imag = &a[1];
  double *z1_real = &a[2];
  double *z1_imag = &a[3];

  // Store the differences
  double diff_real = *z0_real - *z1_real;
  double diff_imag = *z0_imag - *z1_imag;

  // Update the first complex number to be the sum
  *z0_real = *z0_real + *z1_real;
  *z0_imag = *z0_imag + *z1_imag;

  // Update the second complex number to be the previously calculated difference
  *z1_real = diff_real;
  *z1_imag = diff_imag;
}