void __cdecl sub3(double *a1, double *a2)
{
  *a1 = *a1 - *a2;
  a1[1] = a1[1] - a2[1];
  a1[2] = a1[2] - a2[2];
}