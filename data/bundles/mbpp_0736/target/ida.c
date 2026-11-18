int __cdecl func0(int *a, int n, int x)
{
  int mid; // [rsp+0h] [rbp-1Ch]
  int l; // [rsp+8h] [rbp-14h]

  l = 0;
  while ( l < n )
  {
    mid = (n + l) / 2;
    if ( a[mid] >= x )
      n = (n + l) / 2;
    else
      l = mid + 1;
  }
  return l;
}