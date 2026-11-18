// Subtracts the 3D vector a2 from the 3D vector a1 (a1 -= a2)
void __cdecl Vec3Sub(double *a1, double *a2)
{
  a1[0] -= a2[0];
  a1[1] -= a2[1];
  a1[2] -= a2[2];
}