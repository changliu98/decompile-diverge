int __cdecl func0(int *a, int n, int x)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < n && a[i] <= x; ++i )
    ;
  return i;
}