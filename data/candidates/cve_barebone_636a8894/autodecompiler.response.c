static void
f_fullcommand(
    typval_T *args,
    typval_T *rettv)
{
    char_u *p;
    char_u *s;
    int n;
    int vim9script = in_vim9script();
    exarg_T ea;
    int save_cmod_flags = cmdmod.cmod_flags;

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

    if (in_vim9script() && (check_for_string_arg(args, 0) == NULL
                || check_for_opt_bool_arg(args, 1) != 0))
        return;

    p = args[0].vval.v_string;
    if (p == NULL)
        return;

    if (args[1].v_type != VAR_UNKNOWN)
    {
        vim9script = tv_get_bool(&args[1]);
        cmdmod.cmod_flags &= ~(0x4000L | 0x8000L);
        cmdmod.cmod_flags |= (vim9script ? 0x4000L : 0x8000L);
    }

    while (*p == ':')
        ++p;
    p = skip_range(p, true);

    if (*p == '2' || *p == '3')
        s = p + 1;
    else
        s = p;
    ea.cmd = s;
    ea.cmdidx = 0;
    ea.addr_count = 0;

    ++emsg_silent;
    n = find_ex_command(&ea, NULL, NULL);
    --emsg_silent;
    if (n == 0 || ea.cmdidx == 0)
        goto theend;

    if (vim9script)
    {
        ++emsg_silent;
        n = not_in_vim9(&ea);
        --emsg_silent;
        if (n == 0)
            goto theend;
    }

    if (ea.cmdidx < 0)
        s = get_user_command_name(ea.useridx, ea.cmdidx);
    else
        s = cmdnames[ea.cmdidx].name;
    rettv->vval.v_string = vim_strsave(s);

theend:
    cmdmod.cmod_flags = save_cmod_flags;
}