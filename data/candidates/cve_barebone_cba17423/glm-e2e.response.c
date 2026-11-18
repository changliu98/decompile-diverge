const char *ap_limit_section(cmd_parms *cmd, void *dummy, const char *arg) {
    const char *endp = strrchr(arg, '>');
    core_dir_config *conf = (core_dir_config *)cmd->server->module_config; // offset 0x60 -> 0x10
    apr_int64_t limited = 0;
    apr_int64_t old_limited = cmd->limited; // offset 0x18
    const char *errmsg = NULL;
    const char *method;
    int method_number;
    const char *ret;

    if (endp == NULL) {
        return unclosed_directive(cmd);
    }

    char *section_name = apr_pstrmemdup(cmd->pool, arg, endp - arg); // offset 0x48 is cmd->pool
    if (*section_name == '\0') {
        return missing_container_arg(cmd);
    }

    while (*section_name != '\0') {
        method = ap_getword_conf(cmd->pool, &section_name);
        method_number = ap_method_number_of(method);

        if (method_number == 6 && conf->limited == 0) { // 0x10 offset in core_dir_config
            return "<Limit> directive already present"; // String at 0x3004
        }

        if (method_number == 26) {
            void *pool = cmd->temp_pool; // offset 0x40
            char *new_method = apr_pstrdup(pool, method);
            method_number = ap_method_register(pool, new_method);
        }

        limited |= (1LL << method_number);
    }

    if (conf->limited != 0) {
        limited = ~limited;
    }

    if ((old_limited & limited) == 0) {
        return apr_pstrcat(cmd->pool, cmd->server->server_hostname, " ... ", NULL); // String at 0x303b
    }

    if ((old_limited & limited) == old_limited) {
        return apr_pstrcat(cmd->pool, cmd->server->server_hostname, " ... ", NULL); // String at 0x305c
    }

    cmd->limited &= limited;
    ret = ap_walk_config(cmd->directive->first_child, cmd, cmd->context);
    cmd->limited = old_limited;
    
    return ret;
}