int __cdecl eval_tuple(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int do_error)
{
  char_u *v4; // rax
  char_u *v5; // rax
  char_u *v6; // rcx
  bool v8; // [rsp+3h] [rbp-4Dh]
  int v9; // [rsp+4h] [rbp-4Ch]
  int had_comma; // [rsp+8h] [rbp-48h]
  int vim9script; // [rsp+Ch] [rbp-44h]
  typval_T tv; // [rsp+10h] [rbp-40h] BYREF
  tuple_T *tuple; // [rsp+20h] [rbp-30h]
  int evaluate; // [rsp+28h] [rbp-28h]
  int do_errora; // [rsp+2Ch] [rbp-24h]
  evalarg_T *evalarga; // [rsp+30h] [rbp-20h]
  typval_T *rettva; // [rsp+38h] [rbp-18h]
  char_u **arga; // [rsp+40h] [rbp-10h]

  arga = arg;
  rettva = rettv;
  evalarga = evalarg;
  do_errora = do_error;
  if ( evalarg )
    v9 = evalarga->eval_flags & 1;
  else
    v9 = 0;
  evaluate = v9;
  tuple = 0LL;
  vim9script = in_vim9script();
  if ( check_typval_is_value(rettva) )
  {
    if ( evaluate )
    {
      tuple = tuple_alloc();
      if ( !tuple )
        return 0;
      if ( rettva->v_type && !tuple_append_tv(tuple, rettva) )
        return 0;
    }
    if ( **arga == 41 )
    {
done:
      ++*arga;
      if ( evaluate )
        rettv_tuple_set(rettva, tuple);
      return 1;
    }
    else
    {
      if ( !vim9script || (*arga)[1] == 32 || (*arga)[1] == 9 || (*arga)[1] == 10 || !(*arga)[1] || (*arga)[1] == 41 )
      {
        *arga = skipwhite_and_linebreak(*arga + 1, evalarga);
        while ( 1 )
        {
          v8 = 0;
          if ( **arga != 41 )
            v8 = **arga != 0;
          if ( !v8 )
            break;
          if ( !eval1(arga, &tv, evalarga) )
            goto failret;
          if ( !check_typval_is_value(&tv) )
          {
            if ( evaluate )
              clear_tv(&tv);
            goto failret;
          }
          if ( evaluate && !tuple_append_tv(tuple, &tv) )
          {
            clear_tv(&tv);
            goto failret;
          }
          if ( !vim9script )
          {
            v4 = skipwhite(*arga);
            *arga = v4;
          }
          had_comma = **arga == 44;
          if ( **arga == 44 )
          {
            if ( vim9script && (*arga)[1] != 32 && (*arga)[1] != 9 && (*arga)[1] != 10 && (*arga)[1] && (*arga)[1] != 41 )
            {
              semsg("E1069: White space required after '%s': %s", ",", (const char *)*arga);
              goto failret;
            }
            v5 = skipwhite(*arga + 1);
            *arga = v5;
          }
          v6 = skipwhite_and_linebreak(*arga, evalarga);
          *arga = v6;
          if ( **arga == 41 )
            break;
          if ( !had_comma )
          {
            if ( do_errora )
            {
              if ( **arga == 44 )
                semsg("E1068: No white space allowed before '%s': %s", ",", (const char *)*arga);
              else
                semsg("E1527: Missing comma in Tuple: %s", (const char *)*arga);
            }
            goto failret;
          }
        }
        if ( **arga == 41 )
          goto done;
        if ( do_errora )
          semsg("E1526: Missing end of Tuple ')': %s", (const char *)*arga);
      }
      else
      {
        semsg("E1069: White space required after '%s': %s", ",", (const char *)*arga);
      }
failret:
      if ( evaluate )
        tuple_free(tuple);
      return 0;
    }
  }
  else
  {
    clear_tv(rettva);
    return 0;
  }
}