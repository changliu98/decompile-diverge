void __cdecl ecRotate(double *c, double soe, double coe)
{
  double e1; // [rsp+0h] [rbp-20h]

  e1 = c[2] * soe + c[1] * coe;
  c[2] = c[2] * coe - c[1] * soe;
  c[1] = e1;
}