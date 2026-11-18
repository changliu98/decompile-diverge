char *ap_limit_section(cmd_parms *cmd, void *dummy, char *arg)
{
    apr_uint64_t new_limited;
    apr_uint64_t old_limited;
    char *method;
    char *errmsg;
    char *methods;
    char *endp;
    int methnum;
    int allow_trace;

    endp = strrchr(arg, '>');
    allow_trace = cmd->cmd->cmd_data != NULL;
    old_limited = cmd->limited;

    if (endp == NULL)
        return unclosed_directive(cmd);

    methods = apr_pstrmemdup(cmd->temp_pool, arg, endp - arg);

    if (*methods == '\0')
        return missing_container_arg(cmd);

    new_limited = 0;
    while (*methods != '\0') {
        method = ap_getword_conf(cmd->temp_pool, &methods);
        methnum = ap_method_number_of(method);

        if (methnum == 6 && !allow_trace) {
            return "TRACE cannot be controlled by <Limit>, see TraceEnable";
        }

        if (methnum == 26) {
            methnum = ap_method_register(cmd->pool,
                                         apr_pstrdup(cmd->pool, method));
        }

        new_limited |= ((apr_uint64_t)1 << methnum);
    }

    if (allow_trace)
        new_limited = ~new_limited;

    if ((new_limited & old_limited) == 0) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive excludes all methods", NULL);
    }

    if ((new_limited & old_limited) == old_limited) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive specifies methods already excluded",
                           NULL);
    }

    cmd->limited &= new_limited;
    errmsg = ap_walk_config(cmd->directive->first_child, cmd, cmd->context);
    cmd->limited = old_limited;

    return errmsg;
}