void f_fullcommand(arglist_t* argvars, typval_t* rettv) {
    int in_vim9 = in_vim9script();
    int save_cmdmod = cmdmod;
    char* arg;
    char* p;
    char* cmd;
    char* result;
    int eap_cmd;
    int eap_arg;
    int eap_cmdidx;
    int not_in_vim9_res;
    char* saved_str;

    // Initialize return type to string (7) and value to NULL
    rettv->type = 7;
    rettv->str = NULL;

    if (in_vim9) {
        if (check_for_string_arg(argvars, 0) == 0 || 
            check_for_opt_bool_arg(argvars, 1) == 0) {
            goto end;
        }
    }

    arg = argvars->items[0];
    if (arg == NULL) {
        goto end;
    }

    if (argvars->items[1] != NULL) {
        in_vim9 = tv_get_bool(&argvars->items[1]);
        cmdmod &= 0xffff3fff;
        if (in_vim9 != 0) {
            cmdmod |= 0x4000;
        } else {
            cmdmod |= 0x8000;
        }
    }

    // Skip leading colons
    p = arg;
    while (*p == ':') {
        p++;
    }

    p = skip_range(p, 1, NULL);

    if (*p == '2' || *p == '3') {
        cmd = p + 1;
    } else {
        cmd = p;
    }

    eap_cmd = cmd;
    eap_arg = 0;
    eap_cmdidx = 0;

    emsg_silent++;
    find_ex_command(&eap_cmd, &eap_arg, &eap_cmdidx, NULL);
    emsg_silent--;

    if (eap_cmd == NULL || eap_cmdidx == 0) {
        goto end;
    }

    if (in_vim9) {
        emsg_silent++;
        not_in_vim9_res = not_in_vim9(&eap_cmd);
        emsg_silent--;
        if (not_in_vim9_res == 0) {
            goto end;
        }
    }

    if (eap_cmdidx < 0) {
        result = get_user_command_name(eap_arg, eap_cmdidx);
    } else {
        result = cmdnames[eap_cmdidx].name;
    }

    saved_str = vim_strsave(result);
    rettv->str = saved_str;

end:
    cmdmod = save_cmdmod;
}