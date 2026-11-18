double __cdecl func0(double *numbers, int length)
{
  int v2; // ecx
  double result; // [rsp+0h] [rbp-50h]
  double temp; // [rsp+8h] [rbp-48h]
  int j_1; // [rsp+10h] [rbp-40h]
  int i_1; // [rsp+14h] [rbp-3Ch]
  int j_0; // [rsp+18h] [rbp-38h]
  int found; // [rsp+1Ch] [rbp-34h]
  int i_0; // [rsp+20h] [rbp-30h]
  int uniq_length; // [rsp+24h] [rbp-2Ch]
  double *uniq_items; // [rsp+28h] [rbp-28h]
  int j; // [rsp+30h] [rbp-20h]
  int i; // [rsp+34h] [rbp-1Ch]
  int count; // [rsp+38h] [rbp-18h]

  if ( length < 2 )
    return -9999999.0;
  count = 0;
  for ( i = 0; i < length; ++i )
  {
    for ( j = i + 1; j < length; ++j )
    {
      if ( numbers[j] == numbers[i] )
      {
        ++count;
        break;
      }
    }
  }
  if ( length == 2 && count == 1 )
    return -9999999.0;
  uniq_items = (double *)malloc(8LL * length);
  uniq_length = 0;
  for ( i_0 = 0; i_0 < length; ++i_0 )
  {
    found = 0;
    for ( j_0 = 0; j_0 < uniq_length; ++j_0 )
    {
      if ( uniq_items[j_0] == numbers[i_0] )
      {
        found = 1;
        break;
      }
    }
    if ( !found )
    {
      v2 = uniq_length++;
      uniq_items[v2] = numbers[i_0];
    }
  }
  for ( i_1 = 0; i_1 < uniq_length; ++i_1 )
  {
    for ( j_1 = i_1 + 1; j_1 < uniq_length; ++j_1 )
    {
      if ( uniq_items[i_1] > uniq_items[j_1] )
      {
        temp = uniq_items[i_1];
        uniq_items[i_1] = uniq_items[j_1];
        uniq_items[j_1] = temp;
      }
    }
  }
  result = uniq_items[1];
  free(uniq_items);
  return result;
}