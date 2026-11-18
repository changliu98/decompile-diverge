void __cdecl FindDivDiff5Coeff2(double a, double b, double c, double d, double *dd)
{
  double dc; // [rsp+0h] [rbp-58h]
  double db; // [rsp+8h] [rbp-50h]
  double da; // [rsp+10h] [rbp-48h]
  double cb; // [rsp+18h] [rbp-40h]
  double ca; // [rsp+20h] [rbp-38h]
  double ba; // [rsp+28h] [rbp-30h]

  ba = 1.0 / (b - a);
  ca = 1.0 / (c - a);
  cb = 1.0 / (c - b);
  da = 1.0 / (d - a);
  db = 1.0 / (d - b);
  dc = 1.0 / (d - c);
  *dd = -ba * ba * ca * ca * da;
  dd[1] = -(cb + cb + db - ba) * ba * db * cb * cb;
  dd[2] = -ba * db * cb * cb;
  dd[3] = -(dc - (cb + cb) - ca) * dc * ca * cb * cb;
  dd[4] = -dc * ca * cb * cb;
  dd[5] = da * db * db * dc * dc;
}