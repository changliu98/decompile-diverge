void f_fullcommand(typval_T *argvars,typval_T *rettv)

{
  cmdmod_T cVar1;
  cmdmod_T cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  varnumber_T vVar6;
  char_u *pcVar7;
  char_u *local_60;
  char_u *local_58;
  int res;
  int save_cmod_flags;
  int vim9script;
  char_u *p;
  char_u *name;
  exarg_T ea;
  typval_T *rettv_local;
  typval_T *argvars_local;
  
  vim9script = in_vim9script();
  cVar1 = cmdmod;
  rettv->v_type = VAR_STRING;
  (rettv->vval).v_number = 0;
  iVar3 = in_vim9script();
  if (((iVar3 == 0) ||
      ((iVar4 = check_for_string_arg(argvars,0), cVar2 = cmdmod, iVar3 = emsg_silent, iVar4 != 0 &&
       (iVar4 = check_for_opt_bool_arg(argvars,1), cVar2 = cmdmod, iVar3 = emsg_silent, iVar4 != 0))
      )) && (name = (argvars->vval).v_string, cVar2.cmod_flags = cmdmod.cmod_flags,
            iVar3 = emsg_silent, name != (char_u *)0x0)) {
    if (argvars[1].v_type != VAR_UNKNOWN) {
      vVar6 = tv_get_bool(argvars + 1);
      vim9script = (int)vVar6;
      uVar5 = 0x8000;
      if (vim9script != 0) {
        uVar5 = 0x4000;
      }
      cmdmod.cmod_flags = uVar5 | cmdmod.cmod_flags & 0xffff3fffU;
    }
    for (; *name == ':'; name = name + 1) {
    }
    local_58 = skip_range(name,1,(int *)0x0);
    if ((*local_58 == '2') || (*local_58 == '3')) {
      local_58 = local_58 + 1;
    }
    ea.cmd = local_58;
    ea.cmdidx = CMD_SIZE;
    ea.addr_count = 0;
    emsg_silent = emsg_silent + 1;
    pcVar7 = find_ex_command(&ea,(int *)0x0,(_func_int_char_u_ptr_size_t_int_cctx_T_ptr *)0x0,
                             (cctx_T *)0x0);
    iVar3 = emsg_silent + -1;
    cVar2 = cVar1;
    if ((pcVar7 != (char_u *)0x0) && (ea.cmdidx != CMD_SIZE)) {
      if (vim9script != 0) {
        iVar4 = not_in_vim9(&ea);
        iVar3 = emsg_silent + -1;
        if (iVar4 == 0) {
          cmdmod = cVar1;
          emsg_silent = emsg_silent + -1;
          return;
        }
      }
      emsg_silent = iVar3;
      if ((int)ea.cmdidx < 0) {
        local_60 = get_user_command_name(ea.useridx,ea.cmdidx);
      }
      else {
        local_60 = cmdnames[ea.cmdidx].cmd_name;
      }
      pcVar7 = vim_strsave(local_60);
      (rettv->vval).v_string = pcVar7;
      iVar3 = emsg_silent;
    }
  }
  emsg_silent = iVar3;
  cmdmod.cmod_flags = cVar2.cmod_flags;
  return;
}