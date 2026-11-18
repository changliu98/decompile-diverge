int check_key(
  toml_table_t *tbl, char *key,
  toml_keyval_t **ret_val, toml_array_t **ret_arr, toml_table_t **ret_tbl
) {
  int i;
  void *dummy;


  if (!ret_tbl) ret_tbl = (toml_table_t **)&dummy;
  if (!ret_arr) ret_arr = (toml_array_t **)&dummy;
  if (!ret_val) ret_val = (toml_keyval_t **)&dummy;


  *ret_tbl = NULL;
  *ret_arr = NULL;
  *ret_val = NULL;


  for (i = 0; i < tbl->nkval; i++) {
    if (!strcmp(key, tbl->kval[i]->key)) {
      *ret_val = tbl->kval[i];
      return 'v';
    }
  }


  for (i = 0; i < tbl->narr; i++) {
    if (!strcmp(key, tbl->arr[i]->key)) {
      *ret_arr = tbl->arr[i];
      return 'a';
    }
  }


  for (i = 0; i < tbl->ntbl; i++) {
    if (!strcmp(key, tbl->tbl[i]->key)) {
      *ret_tbl = tbl->tbl[i];
      return 't';
    }
  }

  return 0;
}