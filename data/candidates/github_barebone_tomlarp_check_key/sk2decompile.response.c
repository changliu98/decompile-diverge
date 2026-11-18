static char check_key(tpl_node* nd, const char* key, tpl_var** var,
                      tpl_array** arr, tpl_node** tpl) {
  int i;
  tpl_var* v;
  tpl_array* a;
  tpl_node* t;
  if (tpl == NULL) {
    tpl = &t;
  }
  if (arr == NULL) {
    arr = &a;
  }
  if (var == NULL) {
    var = &v;
  }
  *tpl = NULL;
  *arr = NULL;
  *var = NULL;
  for (i = 0; i < nd->num_vars; i++) {
    if (!strcmp(key, nd->vars[i]->key)) {
      *var = nd->vars[i];
      return 'v';
    }
  }
  for (i = 0; i < nd->num_arrays; i++) {
    if (!strcmp(key, nd->arrays[i]->key)) {
      *arr = nd->arrays[i];
      return 'a';
    }
  }
  for (i = 0; i < nd->num_tpls; i++) {
    if (!strcmp(key, nd->tpls[i]->key)) {
      *tpl = nd->tpls[i];
      return 't';
    }
  }
  return 0;
}