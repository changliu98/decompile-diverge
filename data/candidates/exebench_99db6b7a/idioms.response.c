void ifft4pt(float *io, float scale)
{
  float a; float b; float c; float d; float e; float f; float g; float h; float i; float j; float k; float l;
  a = io[0];
  b = io[1];
  c = io[2];
  d = io[3];
  e = io[4];
  f = io[5];
  g = io[6];
  h = io[7];
  i = a + c;
  j = b + d;
  k = a - c;
  l = b - d;
  c = e - g;
  d = f - h;
  e = e + g;
  f = f + h;
  a = i + e;
  b = j + f;
  c = k - d;
  d = l + c;
  e = i - e;
  f = j - f;
  g = k + d;
  h = l - d;
  io[0] = a * scale;
  io[1] = b * scale;
  io[2] = c * scale;
  io[3] = d * scale;
  io[4] = e * scale;
  io[5] = f * scale;
  io[6] = g * scale;
  io[7] = h * scale;
}