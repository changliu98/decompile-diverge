void __cdecl MatrixM(int *a, int *b)
{
  int t4; // [rsp+0h] [rbp-20h]
  int t3; // [rsp+4h] [rbp-1Ch]
  int t2; // [rsp+8h] [rbp-18h]

  t2 = (b[3] * a[1] + b[1] * *a) % 100;
  t3 = (b[2] * a[3] + *b * a[2]) % 100;
  t4 = (b[3] * a[3] + b[1] * a[2]) % 100;
  *a = (b[2] * a[1] + *b * *a) % 100;
  a[1] = t2;
  a[2] = t3;
  a[3] = t4;
}