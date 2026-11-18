void f_fullcommand(arg_t *args, arg_t *result) {
  cmd_t cmd;
  int vim9;
  int save_flags;
  char_u *p;
  char_u *name;
  vim9 = in_vim9script();
  save_flags = cmd_flags;
  result->type = TYPE_STRING;
  result->value.string = 0;
  if (in_vim9script() && (!check_for_string_arg(args, 0)
#ifdef FEAT_GUI
                          || !check_for_opt_bool_arg(args, 1)
#endif
                          ))
    return;
  p = args->value.string;
  if (p == NULL) return;
  if (args[1].type != TYPE_NOTHING) {
    vim9 = tv_get_bool(&args[1]);
    cmd_flags &= ~(0x00000001 | 0x00000002 | 0x00000004 | 0x00000008 |
                   0x00000010 | 0x00000020 | 0x00000040 | 0x00000080 |
                   0x00000100 | 0x00000200 | 0x00000400 | 0x00000800 |
                   0x00001000 | 0x00002000 | 0x00004000 | 0x00008000 |
                   0x00010000 | 0x00020000 | 0x00040000 | 0x00080000 |
                   0x00100000 | 0x00200000 | 0x00400000 | 0x00800000 |
                   0x01000000 | 0x02000000 | 0x04000000 | 0x08000000 |
                   0x10000000 | 0x20000000 | 0x40000000 | 0x80000000);
    cmd_flags |= vim9 ? 0x00004000 : 0x00008000;
  }
  while (*p == ':') ++p;
  p = skip_range(p, 1, NULL);
  if (*p == '2' || *p == '3')
    ++p;
  else
    ;
  cmd.name = p;
  cmd.cmd_id = CMD_NONE;
  cmd.cmd_flags = 0;
  ++in_function;
  p = find_ex_command(&cmd, NULL, 0, 0);
  --in_function;
  if (p != NULL && cmd.cmd_id != 0) {
    if (vim9 && (++in_function, !not_in_vim9(&cmd), --in_function)) {
    } else {
      if (cmd.cmd_id < CMD_NONE)
        name = get_user_command_name(cmd.cmd_name, cmd.cmd_id);
      else
        name = cmd_names[cmd.cmd_id];
      result->value.string = vim_strsave(name);
    }
  }
  cmd_flags = save_flags;
}