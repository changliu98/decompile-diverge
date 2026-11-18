int __cdecl eval_tuple(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int do_error)
{
  typval_T tv;
  tuple_T *tuple = NULL;
  int had_comma;
  int vim9script = in_vim9script();
  int evaluate = (evalarg != NULL) ? (evalarg->eval_flags & 1) : 0;

  if (!check_typval_is_value(rettv))
  {
    clear_tv(rettv);
    return 0;
  }

  if (evaluate)
  {
    tuple = tuple_alloc();
    if (!tuple)
      return 0;
    if (rettv->v_type && !tuple_append_tv(tuple, rettv))
      return 0;
  }

  if (**arg == ')')
    goto done;

  if (vim9script && (*arg)[1] != ' ' && (*arg)[1] != '\t' && (*arg)[1] != '\n' && (*arg)[1] != '\0' && (*arg)[1] != ')')
  {
    semsg("E1069: White space required after '%s': %s", ",", (const char *)*arg);
    goto failret;
  }

  *arg = skipwhite_and_linebreak(*arg + 1, evalarg);
  while (1)
  {
    if (**arg == ')' || **arg == '\0')
      break;

    if (!eval1(arg, &tv, evalarg))
      goto failret;

    if (!check_typval_is_value(&tv))
    {
      if (evaluate)
        clear_tv(&tv);
      goto failret;
    }

    if (evaluate && !tuple_append_tv(tuple, &tv))
    {
      clear_tv(&tv);
      goto failret;
    }

    if (!vim9script)
      *arg = skipwhite(*arg);

    had_comma = (**arg == ',');
    if (**arg == ',')
    {
      if (vim9script && (*arg)[1] != ' ' && (*arg)[1] != '\t' && (*arg)[1] != '\n' && (*arg)[1] != '\0' && (*arg)[1] != ')')
      {
        semsg("E1069: White space required after '%s': %s", ",", (const char *)*arg);
        goto failret;
      }
      *arg = skipwhite(*arg + 1);
    }

    *arg = skipwhite_and_linebreak(*arg, evalarg);
    if (**arg == ')')
      break;

    if (!had_comma)
    {
      if (do_error)
      {
        if (**arg == ',')
          semsg("E1068: No white space allowed before '%s': %s", ",", (const char *)*arg);
        else
          semsg("E1527: Missing comma in Tuple: %s", (const char *)*arg);
      }
      goto failret;
    }
  }

  if (**arg == ')')
  {
done:
    ++*arg;
    if (evaluate)
      rettv_tuple_set(rettv, tuple);
    return 1;
  }

  if (do_error)
    semsg("E1526: Missing end of Tuple ')': %s", (const char *)*arg);

failret:
  if (evaluate)
    tuple_free(tuple);
  return 0;
}