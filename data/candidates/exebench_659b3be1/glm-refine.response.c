void __cdecl bitrv208(float *a)
{
  // Treat the array as an array of 32-bit integers to avoid type punning and pointer arithmetic issues
  int *p = (int *)a;

  // Cache the values that will be overwritten before they are used
  int x1r = p[2];
  int x1i = p[3];
  int x3r = p[6];
  int x3i = p[7];
  int x4i = p[9];
  int x6r = p[12];
  int x6i = p[13];

  // Perform the bit-reversal swaps
  p[2] = p[8];
  p[3] = x4i;
  p[6] = x6r;
  p[7] = x6i;
  p[8] = x1r;
  p[9] = x1i;
  p[12] = x3r;
  p[13] = x3i;
}