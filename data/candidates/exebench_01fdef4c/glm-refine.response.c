void __cdecl cftb040(float a[8])
{
  // Intermediate real and imaginary parts
  float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;

  // Stage 1: Butterfly operations (additions and subtractions)
  x0r = a[0] + a[4];
  x0i = a[1] + a[5];
  x1r = a[0] - a[4];
  x1i = a[1] - a[5];
  
  x2r = a[2] + a[6];
  x2i = a[3] + a[7];
  x3r = a[2] - a[6];
  x3i = a[3] - a[7];

  // Stage 2: Combine and write back to the array
  a[0] = x0r + x2r;
  a[1] = x0i + x2i;
  
  a[2] = x1r + x3i;
  a[3] = x1i - x3r;
  
  a[4] = x0r - x2r;
  a[5] = x0i - x2i;
  
  a[6] = x1r - x3i;
  a[7] = x1i + x3r;
}