void __cdecl ifft4pt(float *ioptr, float scale)
{
  // Load the 4 complex numbers from memory
  float r0 = ioptr[0];
  float i0 = ioptr[1];
  float r1 = ioptr[2];
  float i1 = ioptr[3];
  float r2 = ioptr[4];
  float i2 = ioptr[5];
  float r3 = ioptr[6];
  float i3 = ioptr[7];

  // Stage 1: 2-point DFTs (Butterfly operations)
  // Group A: x0 and x2
  float a0r = r0 + r2;
  float a0i = i0 + i2;
  float a1r = r0 - r2;
  float a1i = i0 - i2;

  // Group B: x1 and x3
  float b0r = r1 + r3;
  float b0i = i1 + i3;
  float b1r = r1 - r3;
  float b1i = i1 - i3;

  // Stage 2: Combine with twiddle factor multiplication
  // The twiddle factor for the 4-point IFFT is W = e^(j*2*pi/4) = j
  // Multiplication by j: (b1r + j*b1i) * j = -b1i + j*b1r
  float t1r = -b1i;
  float t1i =  b1r;

  // Final outputs scaled by 'scale'
  // X0 = a0 + b0
  ioptr[0] = scale * (a0r + b0r);
  ioptr[1] = scale * (a0i + b0i);
  
  // X1 = a1 + t1
  ioptr[2] = scale * (a1r + t1r);
  ioptr[3] = scale * (a1i + t1i);
  
  // X2 = a0 - b0
  ioptr[4] = scale * (a0r - b0r);
  ioptr[5] = scale * (a0i - b0i);
  
  // X3 = a1 - t1
  ioptr[6] = scale * (a1r - t1r);
  ioptr[7] = scale * (a1i - t1i);
}