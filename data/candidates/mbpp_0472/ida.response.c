bool __cdecl func0(int *l, int size)
{
  int i_1; // [rsp+0h] [rbp-30h]
  bool result; // [rsp+7h] [rbp-29h]
  int temp; // [rsp+8h] [rbp-28h]
  int j; // [rsp+Ch] [rbp-24h]
  int i_0; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]
  int *sorted; // [rsp+18h] [rbp-18h]

  sorted = (int *)malloc(4LL * size);
  for ( i = 0; i < size; ++i )
    sorted[i] = l[i];
  for ( i_0 = 0; i_0 < size; ++i_0 )
  {
    for ( j = i_0 + 1; j < size; ++j )
    {
      if ( sorted[i_0] > sorted[j] )
      {
        temp = sorted[i_0];
        sorted[i_0] = sorted[j];
        sorted[j] = temp;
      }
    }
  }
  result = 1;
  for ( i_1 = 1; i_1 < size; ++i_1 )
  {
    if ( sorted[i_1] != sorted[i_1 - 1] + 1 )
    {
      result = 0;
      break;
    }
  }
  free(sorted);
  return result;
}