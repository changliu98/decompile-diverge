int __cdecl func0(int *arr, int n)
{
  int i_0; // [rsp+0h] [rbp-20h]
  int num; // [rsp+4h] [rbp-1Ch]
  int temp; // [rsp+8h] [rbp-18h]
  int j; // [rsp+Ch] [rbp-14h]
  int i; // [rsp+10h] [rbp-10h]

  for ( i = 0; i < n - 1; ++i )
  {
    for ( j = i + 1; j < n; ++j )
    {
      if ( arr[i] < arr[j] )
      {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  num = *arr;
  for ( i_0 = 1; i_0 < n; ++i_0 )
    num = arr[i_0] + 10 * num;
  return num;
}