void __cdecl cmul(double *aa, double *bb)
{
  double ii; // [rsp+0h] [rbp-20h]

  ii = *aa * bb[1] + aa[1] * *bb;
  *aa = *aa * *bb - aa[1] * bb[1];
  aa[1] = ii;
}