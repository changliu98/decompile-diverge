void __cdecl func0(int *my_list, int n)
{
  __int64 v2; // rcx
  int a; // [rsp+Ch] [rbp-34h]
  int j_0; // [rsp+10h] [rbp-30h]
  int pos; // [rsp+14h] [rbp-2Ch]
  int i_0; // [rsp+18h] [rbp-28h]
  int j; // [rsp+1Ch] [rbp-24h]
  int *buckets; // [rsp+20h] [rbp-20h]
  int i; // [rsp+2Ch] [rbp-14h]
  int max_value; // [rsp+30h] [rbp-10h]

  max_value = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( my_list[i] > max_value )
      max_value = my_list[i];
  }
  buckets = (int *)malloc(4LL * (max_value + 1));
  for ( j = 0; j <= max_value; ++j )
    buckets[j] = 0;
  for ( i_0 = 0; i_0 < n; ++i_0 )
  {
    v2 = my_list[i_0];
    ++buckets[v2];
  }
  pos = 0;
  for ( j_0 = 0; j_0 <= max_value; ++j_0 )
  {
    for ( a = 0; a < buckets[j_0]; ++a )
      my_list[pos++] = j_0;
  }
  free(buckets);
}