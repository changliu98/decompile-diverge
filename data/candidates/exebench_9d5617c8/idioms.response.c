void ifft2pt(float *v, float s)
{
  float v1r = v[2];
  float v1i = v[3];
  float v0r = v[0] + v1r;
  float v0i = v[1] + v1i;
  float v1ra = v[0] - v1r;
  float v1ia = v[1] - v1i;
  v[0] = s * v0r;
  v[1] = s * v0i;
  v[2] = s * v1ra;
  v[3] = s * v1ia;
}