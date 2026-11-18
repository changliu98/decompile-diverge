void __cdecl vscale(float *v, float div)
{
  *v = div * *v;
  v[1] = div * v[1];
  v[2] = div * v[2];
}