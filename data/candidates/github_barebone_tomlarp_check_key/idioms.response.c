int check_key(struct toml_table *tbl, char *key, struct toml_keyval **ret_val, struct toml_array **ret_arr, struct toml_table **ret_tbl)
{
  int i;
  if (!ret_tbl) ret_tbl = (struct toml_table **) &((void *)0);
  if (!ret_arr) ret_arr = (struct toml_array **) &((void *)0);
  if (!ret_val) ret_val = (struct toml_keyval **) &((void *)0);
  *ret_tbl = ((void *)0);
  *ret_arr = ((void *)0);
  *ret_val = ((void *)0);
  for (i = 0; i < tbl->nkval; i++)
    if (!strcmp(key, tbl->kval[i]->key)) {
      *ret_val = tbl->kval[i];
      return 'v';
    }
  for (i = 0; i < tbl->narr; i++)
    if (!strcmp(key, tbl->arr[i]->key)) {
      *ret_arr = tbl->arr[i];
      return 'a';
    }
  for (i = 0; i < tbl->ntbl; i++)
    if (!strcmp(key, tbl->tbl[i]->key)) {
      *ret_tbl = tbl->tbl[i];
      return 't';
    }
  return 0;
}