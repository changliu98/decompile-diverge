static int eval_tuple(char **p, typval_T *tv, lex_state_T *ls, int warn) {
  int alloc_tuple = (ls != NULL) ? (ls->flags & 0x0001) : 0;
  tuple_T *t = NULL;
  int in_vimscript = in_vim9script();
  typval_T tv2;
  int comma;
  if (!check_typval_is_value(tv)) {
    clear_tv(tv);
    return 0;
  }
  if (alloc_tuple) {
    t = tuple_alloc();
    if (t == NULL) return 0;
    if (tv->v != 0 && !tuple_append_tv(t, tv)) return 0;
  }
  if (**p == ')') {
    goto done;
  }
  if (in_vimscript && **(p + 1) != ' ' && **(p + 1) != '\t' &&
      **(p + 1) != '\n' && **(p + 1) != '\0' && **(p + 1) != ')') {
    semsg("E1069: White space required after '%s': %s", ",", *p);
    goto failret;
  }
  *p = skipwhite_and_linebreak(*p + 1, ls);
  while (**p != ')' && **p != '\0') {
    if (!eval1(p, &tv2, ls)) goto failret;
    if (!check_typval_is_value(&tv2)) {
      if (alloc_tuple) clear_tv(&tv2);
      goto failret;
    }
    if (alloc_tuple && !tuple_append_tv(t, &tv2)) {
      clear_tv(&tv2);
      goto failret;
    }
    if (!in_vimscript) *p = skipwhite(*p);
    comma = **p == ',';
    if (**p == ',') {
      if (in_vimscript && **(p + 1) != ' ' && **(p + 1) != '\t' &&
          **(p + 1) != '\n' && **(p + 1) != '\0' && **(p + 1) != ')') {
        semsg("E1069: White space required after '%s': %s", ",", *p);
        goto failret;
      }
      *p = skipwhite(*p + 1);
    }
    *p = skipwhite_and_linebreak(*p, ls);
    if (**p == ')') break;
    if (!comma) {
      if (warn) {
        if (**p == ',')
          semsg("E1068: No white space allowed before '%s': %s", ",", *p);
        else
          semsg("E1527: Missing comma in Tuple: %s", *p);
      }
      goto failret;
    }
  }
  if (**p == ')') {
  done:
    (*p)++;
    if (alloc_tuple) rettv_tuple_set(tv, t);
    return 1;
  }
  if (warn) semsg("E1526: Missing end of Tuple ')': %s", *p);
failret:
  if (alloc_tuple) tuple_free(t);
  return 0;
}