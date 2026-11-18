int __cdecl func0(int *a, int *b, int n)
{
  int i; // [rsp+4h] [rbp-1Ch]
  int sum; // [rsp+8h] [rbp-18h]

  sort(a, n);
  sort(b, n);
  sum = 0;
  for ( i = 0; i < n; ++i )
    sum += abs(a[i] - b[i]);
  return sum;
}