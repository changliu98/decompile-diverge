char **__cdecl func0(char **lst, int lst_size, int *return_size)
{
  char **out; // [rsp+0h] [rbp-40h]
  size_t len_j1; // [rsp+8h] [rbp-38h]
  size_t len_j; // [rsp+10h] [rbp-30h]
  char *temp; // [rsp+18h] [rbp-28h]
  int j; // [rsp+20h] [rbp-20h]
  int i; // [rsp+24h] [rbp-1Ch]
  int ia; // [rsp+24h] [rbp-1Ch]
  int ib; // [rsp+24h] [rbp-1Ch]

  *return_size = 0;
  for ( i = 0; i < lst_size; ++i )
  {
    if ( (strlen(lst[i]) & 1) == 0 )
      lst[(*return_size)++] = lst[i];
  }
  for ( ia = 0; ia < *return_size - 1; ++ia )
  {
    for ( j = 0; j < *return_size - ia - 1; ++j )
    {
      len_j = strlen(lst[j]);
      len_j1 = strlen(lst[j + 1]);
      if ( len_j > len_j1 || len_j == len_j1 && strcmp(lst[j], lst[j + 1]) > 0 )
      {
        temp = lst[j];
        lst[j] = lst[j + 1];
        lst[j + 1] = temp;
      }
    }
  }
  out = (char **)malloc(8LL * *return_size);
  for ( ib = 0; ib < *return_size; ++ib )
    out[ib] = lst[ib];
  return out;
}