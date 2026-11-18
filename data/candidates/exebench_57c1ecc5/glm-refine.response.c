void __cdecl cftf081(float *a)
{
  // Stage 1: Size-2 DFTs (Butterfly)
  float x0r = a[0] + a[8];
  float x0i = a[1] + a[9];
  float x1r = a[0] - a[8];
  float x1i = a[1] - a[9];
  float x2r = a[4] + a[12];
  float x2i = a[5] + a[13];
  float x3r = a[4] - a[12];
  float x3i = a[5] - a[13];

  // Stage 2: Size-4 DFTs
  float y0r = x0r + x2r;
  float y0i = x0i + x2i;
  float y2r = x0r - x2r;
  float y2i = x0i - x2i;
  float y1r = x1r - x3i;
  float y1i = x1i + x3r;
  float y3r = x1r + x3i;
  float y3i = x1i - x3r;

  // Stage 1 for odd elements
  float x0ra = a[2] + a[10];
  float x0ia = a[3] + a[11];
  float x1ra = a[2] - a[10];
  float x1ia = a[3] - a[11];
  float x2ra = a[6] + a[14];
  float x2ia = a[7] + a[15];
  float x3ra = a[6] - a[14];
  float x3ia = a[7] - a[15];

  // Stage 2 for odd elements
  float y4r = x0ra + x2ra;
  float y4i = x0ia + x2ia;
  float y6r = x0ra - x2ra;
  float y6i = x0ia - x2ia;

  // Stage 3: Size-8 DFT twiddle factors (1/sqrt(2) = 0.70710677)
  float t1r = x1ra - x3ia;
  float t1i = x1ia + x3ra;
  float t2r = x1ra + x3ia;
  float t2i = x1ia - x3ra;

  float y5r = 0.70710677f * (t1r - t1i);
  float y5i = 0.70710677f * (t1r + t1i);
  float y7r = 0.70710677f * (t2r - t2i);
  float y7i = 0.70710677f * (t2r + t2i);

  // Stage 3: Final combinations
  a[0]  = y0r + y4r;
  a[1]  = y0i + y4i;
  a[2]  = y0r - y4r;
  a[3]  = y0i - y4i;
  a[4]  = y2r - y6i;
  a[5]  = y2i + y6r;
  a[6]  = y2r + y6i;
  a[7]  = y2i - y6r;
  a[8]  = y1r + y5r;
  a[9]  = y1i + y5i;
  a[10] = y1r - y5r;
  a[11] = y1i - y5i;
  a[12] = y3r - y7i;
  a[13] = y3i + y7r;
  a[14] = y3r + y7i;
  a[15] = y3i - y7r;
}