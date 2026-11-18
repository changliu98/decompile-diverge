void __cdecl mult(double *A, const double *a, double *b)
{
  int v3; // ecx
  int i; // [rsp+0h] [rbp-20h]
  int c; // [rsp+4h] [rbp-1Ch]

  c = 0;
  i = 0;
  while ( c < 4 )
  {
    b[c] = A[i] * *a;
    b[c] = A[i + 1] * a[1] + b[c];
    b[c] = A[i + 2] * a[2] + b[c];
    v3 = i + 3;
    i += 4;
    b[c] = A[v3] * a[3] + b[c];
    ++c;
  }
}