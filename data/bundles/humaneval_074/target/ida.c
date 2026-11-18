char **__cdecl func0(char **arr1, int n1, char **arr2, int n2)
{
  int sum2; // [rsp+0h] [rbp-30h]
  int sum1; // [rsp+4h] [rbp-2Ch]
  int i; // [rsp+8h] [rbp-28h]
  int ia; // [rsp+8h] [rbp-28h]

  sum1 = 0;
  sum2 = 0;
  for ( i = 0; i < n1; ++i )
    sum1 += strlen(arr1[i]);
  for ( ia = 0; ia < n2; ++ia )
    sum2 += strlen(arr2[ia]);
  if ( sum1 < sum2 )
    return arr1;
  if ( sum1 <= sum2 )
    return arr1;
  return arr2;
}