void fft4pt(float *iovec)
{
  float ivec0r; float ivec1r; float ivec2r; float ivec3r;
  float ivec0i; float ivec1i; float ivec2i; float ivec3i;
  float ivec1ra; float ivec1ia;
  float ivec2a;
  float ivec3a;
  ivec0r = iovec[0];
  ivec1r = iovec[4];
  ivec1i = iovec[5];
  ivec2r = iovec[1];
  ivec2i = iovec[2];
  ivec3r = iovec[6];
  ivec3i = iovec[7];
  ivec1ra = ivec0r - ivec1r;
  ivec1ia = ivec0i - ivec1i;
  ivec2a = ivec0r + ivec1r;
  ivec3a = ivec0i + ivec1i;
  ivec0r = ivec2a + ivec3r;
  ivec0i = ivec3a + ivec3i;
  ivec1r = ivec1ra - ivec3i;
  ivec1i = ivec1ia + ivec3r;
  ivec2a = ivec2a - ivec3r;
  ivec3a = ivec3a - ivec3i;
  ivec1ra = ivec1ra - ivec2i;
  ivec1ia = ivec1ia - ivec2r;
  iovec[0] = ivec0r;
  iovec[1] = ivec0i;
  iovec[2] = ivec1r;
  iovec[3] = ivec1i;
  iovec[4] = ivec2a;
  iovec[5] = ivec3a;
  iovec[6] = ivec1ra;
  iovec[7] = ivec1ia;
}