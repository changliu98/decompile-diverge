void __cdecl f_fullcommand(typval_T *argvars, typval_T *rettv)
{
  int v2; // eax
  char_u *v3; // rax
  int v4; // eax
  char_u *v5; // rax
  char_u *string; // [rsp+8h] [rbp-58h]
  char_u *v7; // [rsp+10h] [rbp-50h]
  int save_cmod_flags; // [rsp+20h] [rbp-40h]
  int vim9script; // [rsp+24h] [rbp-3Ch]
  char_u *name; // [rsp+30h] [rbp-30h]
  char_u *namea; // [rsp+30h] [rbp-30h]
  exarg_T ea; // [rsp+38h] [rbp-28h] BYREF
  typval_T *rettva; // [rsp+50h] [rbp-10h]
  typval_T *argvarsa; // [rsp+58h] [rbp-8h]

  argvarsa = argvars;
  rettva = rettv;
  vim9script = in_vim9script();
  save_cmod_flags = cmdmod;
  rettv->v_type = VAR_STRING;
  rettva->vval.v_number = 0LL;
  if ( !in_vim9script() || check_for_string_arg(argvarsa, 0) && check_for_opt_bool_arg(argvarsa, 1) )
  {
    name = argvarsa->vval.v_string;
    if ( name )
    {
      if ( argvarsa[1].v_type )
      {
        vim9script = tv_get_bool(argvarsa + 1);
        cmdmod &= 0xFFFF3FFF;
        v2 = 0x8000;
        if ( vim9script )
          v2 = 0x4000;
        cmdmod |= v2;
      }
      while ( *name == 58 )
        ++name;
      namea = skip_range(name, 1, 0LL);
      if ( *namea == 50 || *namea == 51 )
        v7 = namea + 1;
      else
        v7 = namea;
      ea.cmd = v7;
      ea.cmdidx = CMD_SIZE;
      ea.addr_count = 0;
      ++emsg_silent;
      v3 = find_ex_command(&ea, 0LL, 0LL, 0LL);
      --emsg_silent;
      if ( v3 )
      {
        if ( ea.cmdidx )
        {
          if ( !vim9script || (++emsg_silent, v4 = not_in_vim9(&ea), --emsg_silent, v4) )
          {
            if ( ea.cmdidx >= CMD_SIZE )
            {
              v5 = vim_strsave((char_u *)*(&cmdnames + 4 * (unsigned int)ea.cmdidx));
            }
            else
            {
              string = get_user_command_name(ea.useridx, ea.cmdidx);
              v5 = vim_strsave(string);
            }
            rettva->vval.v_number = (varnumber_T)v5;
          }
        }
      }
      cmdmod = save_cmod_flags;
    }
  }
}