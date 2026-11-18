void __cdecl bitrv208(double (*a)[2])
{
  // Temporary variables to store the complex numbers being swapped
  double x1r = a[1][0]; // Re(a[1])
  double x1i = a[1][1]; // Im(a[1])
  double x3r = a[3][0]; // Re(a[3])
  double x3i = a[3][1]; // Im(a[3])
  double x4i = a[4][1]; // Im(a[4])
  double x6r = a[6][0]; // Re(a[6])
  double x6i = a[6][1]; // Im(a[6])

  // Perform the bit-reversal swaps
  a[1][0] = a[4][0]; // Re(a[1]) <- Re(a[4])
  a[1][1] = x4i;     // Im(a[1]) <- Im(a[4])

  a[3][0] = x6r;     // Re(a[3]) <- Re(a[6])
  a[3][1] = x6i;     // Im(a[3]) <- Im(a[6])

  a[4][0] = x1r;     // Re(a[4]) <- Re(a[1])
  a[4][1] = x1i;     // Im(a[4]) <- Im(a[1])

  a[6][0] = x3r;     // Re(a[6]) <- Re(a[3])
  a[6][1] = x3i;     // Im(a[6]) <- Im(a[3])
}