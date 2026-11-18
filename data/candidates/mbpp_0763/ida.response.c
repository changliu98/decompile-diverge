int __cdecl func0(int *arr, int n)
{
  int diff; // [rsp+0h] [rbp-1Ch]
  int temp; // [rsp+4h] [rbp-18h]
  int j; // [rsp+8h] [rbp-14h]
  int i; // [rsp+Ch] [rbp-10h]
  int ia; // [rsp+Ch] [rbp-10h]

  for ( i = 0; i < n - 1; ++i )
  {
    for ( j = 0; j < n - i - 1; ++j )
    {
      if ( arr[j] > arr[j + 1] )
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  diff = 0x7FFFFFFF;
  for ( ia = 0; ia < n - 1; ++ia )
  {
    if ( arr[ia + 1] - arr[ia] < diff )
      diff = arr[ia + 1] - arr[ia];
  }
  return diff;
}