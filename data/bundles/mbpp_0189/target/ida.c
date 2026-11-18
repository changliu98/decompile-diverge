int __cdecl func0(int *arr, int n)
{
  __int64 v2; // rcx
  int i_2; // [rsp+10h] [rbp-28h]
  int i_1; // [rsp+14h] [rbp-24h]
  int i_0; // [rsp+18h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-1Ch]
  int ptr; // [rsp+20h] [rbp-18h]

  ptr = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( arr[i] == 1 )
    {
      ptr = 1;
      break;
    }
  }
  if ( !ptr )
    return 1;
  for ( i_0 = 0; i_0 < n; ++i_0 )
  {
    if ( arr[i_0] <= 0 || arr[i_0] > n )
      arr[i_0] = 1;
  }
  for ( i_1 = 0; i_1 < n; ++i_1 )
  {
    v2 = (arr[i_1] - 1) % n;
    arr[v2] += n;
  }
  for ( i_2 = 0; i_2 < n; ++i_2 )
  {
    if ( arr[i_2] <= n )
      return i_2 + 1;
  }
  return n + 1;
}