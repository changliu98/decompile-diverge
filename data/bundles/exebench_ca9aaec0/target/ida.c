void __cdecl cross(double *va, double *vb, double *vc)
{
  vc[1] = va[2] * vb[3] - va[3] * vb[2];
  vc[2] = va[3] * vb[1] - va[1] * vb[3];
  vc[3] = va[1] * vb[2] - va[2] * vb[1];
}