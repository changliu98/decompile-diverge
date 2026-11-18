int __cdecl check_key(
        toml_table_t *tbl,
        const char *key,
        toml_keyval_t **ret_val,
        toml_array_t **ret_arr,
        toml_table_t **ret_tbl)
{
  void *dummy = NULL; // Dummy sink for unused output parameters
  int i;
  
  // Redirect NULL output pointers to the dummy sink
  toml_table_t **out_tbl = ret_tbl ? ret_tbl : (toml_table_t **)&dummy;
  toml_array_t **out_arr = ret_arr ? ret_arr : (toml_array_t **)&dummy;
  toml_keyval_t **out_val = ret_val ? ret_val : (toml_keyval_t **)&dummy;

  // Initialize output pointers to NULL
  *out_tbl = NULL;
  *out_arr = NULL;
  *out_val = NULL;

  // Search for a key-value pair
  for ( i = 0; i < tbl->nkval; ++i )
  {
    if ( !strcmp(key, tbl->kval[i]->key) )
    {
      *out_val = tbl->kval[i];
      return 118; // ASCII 'v' for value
    }
  }

  // Search for an array
  for ( i = 0; i < tbl->narr; ++i )
  {
    if ( !strcmp(key, tbl->arr[i]->key) )
    {
      *out_arr = tbl->arr[i];
      return 97;  // ASCII 'a' for array
    }
  }

  // Search for a nested table
  for ( i = 0; i < tbl->ntbl; ++i )
  {
    if ( !strcmp(key, tbl->tbl[i]->key) )
    {
      *out_tbl = tbl->tbl[i];
      return 116; // ASCII 't' for table
    }
  }

  return 0; // Not found
}