void __cdecl func0(int *arr, int len)
{
  int i_0; // [rsp+8h] [rbp-28h]
  int i; // [rsp+Ch] [rbp-24h]
  int *right; // [rsp+10h] [rbp-20h]
  int *left; // [rsp+18h] [rbp-18h]
  int mid; // [rsp+20h] [rbp-10h]

  if ( len >= 2 )
  {
    mid = len / 2;
    left = (int *)malloc(4LL * (len / 2));
    right = (int *)malloc(4LL * (len - len / 2));
    for ( i = 0; i < mid; ++i )
      left[i] = arr[i];
    for ( i_0 = len / 2; i_0 < len; ++i_0 )
      right[i_0 - mid] = arr[i_0];
    func0(left, mid);
    func0(right, len - mid);
    merge(left, mid, right, len - mid, arr);
    free(left);
    free(right);
  }
}