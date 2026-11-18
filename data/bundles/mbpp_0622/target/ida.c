float __cdecl func0(int *arr1, int *arr2, int n)
{
  int count; // [rsp+0h] [rbp-28h]
  int m2; // [rsp+4h] [rbp-24h]
  int m1; // [rsp+8h] [rbp-20h]
  int j; // [rsp+Ch] [rbp-1Ch]
  int i; // [rsp+10h] [rbp-18h]

  i = 0;
  j = 0;
  m1 = -1;
  m2 = -1;
  count = 0;
  while ( count < n + 1 )
  {
    ++count;
    if ( i == n )
    {
      m1 = m2;
      m2 = *arr2;
      return (double)(m2 + m1) / 2.0;
    }
    if ( j == n )
    {
      m1 = m2;
      m2 = *arr1;
      return (double)(m2 + m1) / 2.0;
    }
    m1 = m2;
    if ( arr1[i] > arr2[j] )
      m2 = arr2[j++];
    else
      m2 = arr1[i++];
  }
  return (double)(m2 + m1) / 2.0;
}