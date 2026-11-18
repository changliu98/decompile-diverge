int __cdecl func0(int *ar, int N)
{
  int mid; // [rsp+0h] [rbp-20h]
  int r; // [rsp+4h] [rbp-1Ch]
  int l; // [rsp+8h] [rbp-18h]

  l = 0;
  r = N - 1;
  while ( l <= r )
  {
    mid = (r + l) / 2;
    if ( ar[mid] != mid + 1 && ar[mid - 1] == mid )
      return mid + 1;
    if ( ar[mid] == mid + 1 )
      l = mid + 1;
    else
      r = mid - 1;
  }
  return -1;
}