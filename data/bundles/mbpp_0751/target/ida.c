bool __cdecl func0(int *arr, int n, int i)
{
  bool v4; // [rsp+2h] [rbp-1Eh]
  bool v5; // [rsp+3h] [rbp-1Dh]
  char v6; // [rsp+4h] [rbp-1Ch]
  bool v7; // [rsp+5h] [rbp-1Bh]

  if ( 2 * i + 2 > n )
    return 1;
  v7 = 0;
  if ( arr[i] <= arr[2 * i + 1] )
    v7 = func0(arr, n, 2 * i + 1);
  v6 = 1;
  if ( 2 * i + 2 != n )
  {
    v5 = 0;
    if ( arr[i] <= arr[2 * i + 2] )
      v5 = func0(arr, n, 2 * i + 2);
    v6 = v5;
  }
  v4 = 0;
  if ( v7 )
    return v6 & 1;
  return v4;
}