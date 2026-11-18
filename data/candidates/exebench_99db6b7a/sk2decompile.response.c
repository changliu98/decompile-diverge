void ifft4pt(float *a, float scale) {
  float a0r, a0i, a1r, a1i, a2r, a2i, a3r, a3i;
  a0r = a[0];
  a0i = a[1];
  a1r = a[2];
  a1i = a[3];
  a2r = a[4];
  a2i = a[5];
  a3r = a[6];
  a3i = a[7];
  a0r += a2r;
  a0i += a2i;
  a2r = a0r - a2r;
  a2i = a0i - a2i;
  a1r -= a3r;
  a1i -= a3i;
  a3r += a1r;
  a3i += a1i;
  a[0] = scale * (a0r + a3r);
  a[1] = scale * (a0i + a3i);
  a[2] = scale * (a2r - a1i);
  a[3] = scale * (a2i + a1r);
  a[4] = scale * (a0r - a3r);
  a[5] = scale * (a0i - a3i);
  a[6] = scale * (a2r + a1i);
  a[7] = scale * (a2i - a1r);
}