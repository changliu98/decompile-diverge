void __cdecl cftx020(double *a)
{
  double x0i; // [rsp+0h] [rbp-18h]
  double x0r; // [rsp+8h] [rbp-10h]

  x0r = *a - a[2];
  x0i = a[1] - a[3];
  *a = a[2] + *a;
  a[1] = a[3] + a[1];
  a[2] = x0r;
  a[3] = x0i;
}