void __cdecl vec3Cross(double *v, double *w, double *vCrossW)
{
  *vCrossW = v[1] * w[2] - w[1] * v[2];
  vCrossW[1] = *w * v[2] - *v * w[2];
  vCrossW[2] = *v * w[1] - *w * v[1];
}