int eval_tuple(char **str, struct typval *rettv, struct evalarg *evalarg, int do_error)
{
  int eval = (evalarg ? (evalarg->eval_flags & 1) : 0);
  struct typval tv;
  struct tuple *tup = ((void *)0);
  int vim9script = is_vim9script();
  if (is_rettv(&tv))
  {
    if (eval)
    {
      if ((tup = new_tuple()) == ((void *)0))
        return (0);
      if (rettv->v_type != T_UNDEF && !add_to_tuple(tup, rettv))
        return (0);
    }
    if (**str == ')')
    {
      ++(*str);
      if (eval)
        eval_rettv(&tv, tup);
      return (1);
    }
    if (vim9script &&
        (*str)[1] != ' ' &&
        (*str)[1] != '\t' &&
        (*str)[1] != '\n' &&
        (*str)[1] != '\0' &&
        (*str)[1] != ')')
    {
      msg_E1069("White space required after '%s': %s", ",", *str);
      goto failret;
    }
    *str = next_arg(*str + 1, evalarg);
    while (1)
    {
      int is_end = (**str == ')' || (**str == '\0' ? 0 : 1));
      if (!is_end)
      {
        if (eval_arg(str, &tv, evalarg))
        {
          if (is_rettv(&tv))
          {
            if (eval && !add_to_tuple(tup, &tv))
            {
              eval_rettv(&tv);
              goto failret;
            }
            if (!vim9script)
              *str = next_arg(*str + 1, evalarg);
            int had_comma = (**str == ',');
            if (**str == ',')
            {
              if (vim9script &&
                  (*str)[1] != ' ' &&
                  (*str)[1] != '\t' &&
                  (*str)[1] != '\n' &&
                  (*str)[1] != '\0' &&
                  (*str)[1] != ')')
              {
                msg_E1069("White space required after '%s': %s", ",", *str);
                goto failret;
              }
              *str = next_arg(*str + 1);
            }
            *str = next_arg(*str, evalarg);
            if (**str == ')')
              break;
            if (had_comma)
              continue;
            if (do_error)
            {
              if (**str == ',')
                msg_E1068("No white space allowed before '%s': %s", ",", *str);
              else
                msg_E1527("Missing comma in Tuple: %s", *str);
            }
            goto failret;
          }
          else
          {
            eval_rettv(&tv);
            goto failret;
          }
        }
      }
      if (**str == ')')
      {
        ++(*str);
        if (eval)
          free_tuple(tup);
        return (1);
      }
      if (do_error)
      {
        if (**str == ',')
          msg_E1068("No white space allowed before '%s': %s", ",", *str);
        else
          msg_E1527("Missing end of Tuple ')': %s", *str);
      }
      goto failret;
    }
  }
  else
  {
    eval_rettv(&tv);
    return (0);
  }
failret:
  if (eval)
    free_tuple(tup);
  return (0);
}