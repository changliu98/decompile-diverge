int check_key(toml_table_t *tbl,char *key,toml_keyval_t **ret_val,toml_array_t **ret_arr,
             toml_table_t **ret_tbl)

{
  int iVar1;
  void *dummy;
  int i;
  toml_table_t **ret_tbl_local;
  toml_array_t **ret_arr_local;
  toml_keyval_t **ret_val_local;
  char *key_local;
  toml_table_t *tbl_local;
  
  ret_tbl_local = ret_tbl;
  if (ret_tbl == (toml_table_t **)0x0) {
    ret_tbl_local = &dummy;
  }
  ret_arr_local = ret_arr;
  if (ret_arr == (toml_array_t **)0x0) {
    ret_arr_local = &dummy;
  }
  ret_val_local = ret_val;
  if (ret_val == (toml_keyval_t **)0x0) {
    ret_val_local = &dummy;
  }
  key_local = key;
  tbl_local = tbl;
  *ret_tbl_local = (toml_table_t *)0x0;
  *ret_arr_local = (toml_array_t *)0x0;
  *ret_val_local = (toml_keyval_t *)0x0;
  for (i = 0; i < tbl_local->nkval; i = i + 1) {
    iVar1 = strcmp(key_local,tbl_local->kval[i]->key);
    if (iVar1 == 0) {
      *ret_val_local = tbl_local->kval[i];
      return 0x76;
    }
  }
  for (i = 0; i < tbl_local->narr; i = i + 1) {
    iVar1 = strcmp(key_local,tbl_local->arr[i]->key);
    if (iVar1 == 0) {
      *ret_arr_local = tbl_local->arr[i];
      return 0x61;
    }
  }
  i = 0;
  while( true ) {
    if (tbl_local->ntbl <= i) {
      return 0;
    }
    iVar1 = strcmp(key_local,tbl_local->tbl[i]->key);
    if (iVar1 == 0) break;
    i = i + 1;
  }
  *ret_tbl_local = tbl_local->tbl[i];
  return 0x74;
}