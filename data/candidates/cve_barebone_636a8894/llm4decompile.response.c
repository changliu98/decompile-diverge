void
f_fullcommand(typval_T *argvars, typval_T *rettv)
{
    char_u	*cmd;
    char_u	*s;
    exarg_T	ea;
    int		save_cmod_flags;
    int		vim9script = in_vim9script();

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

    if (in_vim9script()
	    && (!check_for_string_arg(argvars, 0)
		|| !check_for_opt_bool_arg(argvars, 1)))
	return;

    if (argvars[0].vval.v_string == NULL)
	return;

    if (argvars[1].v_type != VAR_UNKNOWN)
	vim9script = (int)tv_get_bool(&argvars[1]);

    /* Save the current cmdmod flags and set the CMD_NO_CONFIRM flag. */
    save_cmod_flags = cmdmod.cmod_flags;
    cmdmod.cmod_flags &= ~(0x00004000 | 0x00008000);
    if (vim9script)
	cmdmod.cmod_flags |= 0x00004000;
    else
	cmdmod.cmod_flags |= 0x00008000;

    /* Skip the first colon, but not the second or third one. */
    for (s = argvars[0].vval.v_string; *s == ':'; ++s)
	;
    s = skip_range(s, 1, NULL);
    if (*s == '2' || *s == '3')
	++s;

    ea.cmd = s;
    ea.cmdidx = CMD_SIZE;
    ea.addr_count = 0;

    /* find_ex_command() may give an error message, which we don't want here */
    ++emsg_silent;
    cmd = find_ex_command(&ea, 0, NULL, NULL);
    --emsg_silent;

    /* restore the saved cmdmod flags */
    cmdmod.cmod_flags = save_cmod_flags;

    if (cmd != NULL && ea.cmdidx != CMD_SIZE
		&& (!vim9script || !not_in_vim9(&ea)))
    {
	if (ea.cmdidx >= 0)
	    s = cmdnames[ea.cmdidx].cmd_name;
	else
	    s = get_user_command_name(ea.useridx, ea.cmdidx);
	rettv->vval.v_string = vim_strsave(s);
    }
}