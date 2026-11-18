char *limit_set(struct cmd_parms *cmd, void *dummy, char *arg)
{
    char *end = strchr(arg, '>');
    int *limited = (int *)cmd->cmd->cmd_data;
    int *old_limited = (int *)cmd->limited;
    char *method; char *methods;
    int methnum;
    char *errmsg;
    if (end == ((void *)0))
        return limit_all(cmd);
    methods = ap_strndup(cmd->temp_pool, arg, end - arg);
    if (methods[0] == '\0')
        return limit_none(cmd);
    for ( ; *methods != '\0'; )
    {
        method = ap_strtok(cmd->temp_pool, &methods);
        methnum = ap_get_method_num(method);
        if (methnum == 6 && limited == ((void *)0))
            return "TRACE cannot be controlled by <Limit>, see TraceEnable";
        if (methnum == 26)
        {
            struct ap_str_struct *str = (ap_str_t *)ap_str_new(cmd->pool, method);
            methnum = ap_get_method_num(ap_str_cstr(str));
        }
        *limited |= (1 << methnum);
    }
    if (limited == ((void *)0))
        *limited = ~old_limited;
    else
        *limited = ~*limited & old_limited;
    if (*limited == 0)
        return ap_log_error(cmd->pool, cmd->cmd->name, "> directive excludes all methods", ((void *)0));
    if (*limited == old_limited)
        return ap_log_error(cmd->pool, cmd->cmd->name, "> directive specifies methods already excluded", ((void *)0));
    cmd->limited = (void *)limited;
    errmsg = limit_check(cmd->directive->first_child, cmd, cmd->context);
    cmd->limited = (void *)old_limited;
    return errmsg;
}