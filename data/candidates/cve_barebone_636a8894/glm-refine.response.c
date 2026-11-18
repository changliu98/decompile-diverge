void __cdecl f_fullcommand(typval_T *argvars, typval_T *rettv)
{
  char_u *name;
  char_u *cmd_start;
  char_u *cmd_name;
  char_u *result_str;
  int save_cmod_flags;
  int is_vim9script;
  int use_vim9_syntax;
  exarg_T ea;

  // Initialize return value to a null string
  rettv->v_type = VAR_STRING;
  rettv->vval.v_number = 0;

  is_vim9script = in_vim9script();
  save_cmod_flags = cmdmod;

  // Validate arguments based on script context
  if (!is_vim9script || (check_for_string_arg(argvars, 0) && check_for_opt_bool_arg(argvars, 1)))
  {
    name = argvars[0].vval.v_string;
    if (name)
    {
      // Check and apply optional boolean argument for Vim9 syntax compatibility
      if (argvars[1].v_type != VAR_UNKNOWN)
      {
        use_vim9_syntax = tv_get_bool(&argvars[1]);
        cmdmod &= ~0xC000; // Clear both flags (0x4000 and 0x8000)
        
        if (use_vim9_syntax)
          cmdmod |= 0x4000;
        else
          cmdmod |= 0x8000;
      }

      // Skip leading colons (':')
      while (*name == ':')
        ++name;

      // Skip range expressions (e.g., %, '<, '>, or numeric ranges)
      cmd_start = skip_range(name, 1, NULL);

      // Skip optional '2' or '3' command modifiers (e.g., 2match, 3match)
      if (*cmd_start == '2' || *cmd_start == '3')
        ++cmd_start;

      // Initialize exarg_T structure for command lookup
      ea.cmd = cmd_start;
      ea.cmdidx = CMD_SIZE;
      ea.addr_count = 0;

      // Find the ex command, suppressing error messages during the lookup
      ++emsg_silent;
      find_ex_command(&ea, NULL, NULL, NULL);
      --emsg_silent;

      if (ea.cmdidx != 0)
      {
        // Check if the command is valid in Vim9 script context
        if (!is_vim9script || not_in_vim9(&ea))
        {
          if (ea.cmdidx >= CMD_SIZE)
          {
            // Built-in command: fetch name from the cmdnames array
            cmd_name = *(char_u **)(&cmdnames + 4 * (unsigned int)ea.cmdidx);
          }
          else
          {
            // User-defined command: fetch its name
            cmd_name = get_user_command_name(ea.useridx, ea.cmdidx);
          }

          // Duplicate the string and assign it to the return value
          result_str = vim_strsave(cmd_name);
          rettv->vval.v_number = (varnumber_T)result_str;
        }
      }

      // Restore the original command modifier flags
      cmdmod = save_cmod_flags;
    }
  }
}