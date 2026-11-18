int *__cdecl func0(int n)
{
  int i; // [rsp+Ch] [rbp-14h]
  int *out; // [rsp+10h] [rbp-10h]

  out = (int *)malloc(4LL * n);
  *out = n;
  for ( i = 1; i < n; ++i )
    out[i] = out[i - 1] + 2;
  return out;
}