void do_ex(struct typval *argvars, struct typval *rettv)
{
  struct exarg ea;
  int save_cmdmod;
  int vim9script;
  char *arg1;
  char *arg2;
  char *cmd;
  int i;
  int ret;
  int ret2;
  int ret3;
  vim9script = is_vim9();
  save_cmdmod = cmdmod;
  rettv->v_type = VAR_STRING;
  rettv->vval.v_string = ((void *)0);
  if (is_vim9() && (is_arg(argvars, 0) == 0))
  {
    return;
  }
  if (is_arg(argvars, 1) == 0)
  {
    return;
  }
  arg1 = argvars[0].vval.v_string;
  if (arg1 == ((void *)0))
  {
    return;
  }
  if (argvars[1].v_type != VAR_NONE)
  {
    vim9script = is_arg(&argvars[1]);
    cmdmod &= ~((1 << 14) | (1 << 15));
    cmdmod |= (vim9script ? (1 << 13) : 0);
  }
  while (*arg1 == ':')
  {
    arg1++;
  }
  arg1 = is_arg_str(arg1, 1, ((void *)0));
  if (*arg1 == '2' || *arg1 == '3')
  {
    arg2 = arg1 + 1;
  }
  else
  {
    arg2 = arg1;
  }
  ea.cmd = arg2;
  ea.cmdidx = CMD_SIZE;
  ea.addr_count = 0;
  emsg_silent++;
  cmd = get_cmd(&ea);
  emsg_silent--;
  if (cmd == ((void *)0))
  {
    return;
  }
  if (ea.cmdidx == 0)
  {
    return;
  }
  if (vim9script)
  {
    emsg_silent++;
    ret = is_cmd_ex(&ea);
    emsg_silent--;
    if (ret == 0)
    {
      return;
    }
  }
  if (ea.cmdidx < CMD_SIZE)
  {
    ret = get_cmd_name(ea.useridx, ea.cmdidx);
  }
  else
  {
    ret = get_cmd_name(ea.useridx, ea.cmdidx);
  }
  ret = get_cmd_name(ea.useridx, ea.cmdidx);
  rettv->vval.v_string = ret;
}