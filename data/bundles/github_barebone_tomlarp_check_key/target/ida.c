int __cdecl check_key(
        toml_table_t *tbl,
        const char *key,
        toml_keyval_t **ret_val,
        toml_array_t **ret_arr,
        toml_table_t **ret_tbl)
{
  void *dummy; // [rsp+0h] [rbp-40h] BYREF
  int i; // [rsp+Ch] [rbp-34h]
  toml_table_t **ret_tbla; // [rsp+10h] [rbp-30h]
  toml_array_t **ret_arra; // [rsp+18h] [rbp-28h]
  toml_keyval_t **ret_vala; // [rsp+20h] [rbp-20h]
  const char *keya; // [rsp+28h] [rbp-18h]
  toml_table_t *tbla; // [rsp+30h] [rbp-10h]

  tbla = tbl;
  keya = key;
  ret_vala = ret_val;
  ret_arra = ret_arr;
  ret_tbla = ret_tbl;
  if ( !ret_tbl )
    ret_tbla = (toml_table_t **)&dummy;
  if ( !ret_arra )
    ret_arra = (toml_array_t **)&dummy;
  if ( !ret_vala )
    ret_vala = (toml_keyval_t **)&dummy;
  *ret_tbla = 0LL;
  *ret_arra = 0LL;
  *ret_vala = 0LL;
  for ( i = 0; i < tbla->nkval; ++i )
  {
    if ( !strcmp(keya, tbla->kval[i]->key) )
    {
      *ret_vala = tbla->kval[i];
      return 118;
    }
  }
  for ( i = 0; i < tbla->narr; ++i )
  {
    if ( !strcmp(keya, tbla->arr[i]->key) )
    {
      *ret_arra = tbla->arr[i];
      return 97;
    }
  }
  for ( i = 0; i < tbla->ntbl; ++i )
  {
    if ( !strcmp(keya, tbla->tbl[i]->key) )
    {
      *ret_tbla = tbla->tbl[i];
      return 116;
    }
  }
  return 0;
}