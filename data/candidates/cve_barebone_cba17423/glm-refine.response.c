const char *__cdecl ap_limit_section(cmd_parms *cmd, void *dummy, const char *arg)
{
  const char *endp = strrchr(arg, '>');
  void *tog = cmd->cmd->cmd_data;
  apr_int64_t limited = 0LL;
  apr_int64_t old_limited = cmd->limited;

  if (!endp)
    return unclosed_directive(cmd);

  const char *limited_methods = apr_pstrmemdup(cmd->temp_pool, arg, endp - arg);
  if (!*limited_methods)
    return missing_container_arg(cmd);

  while (*limited_methods)
  {
    const char *method = ap_getword_conf(cmd->temp_pool, &limited_methods);
    int methnum = ap_method_number_of(method);

    if (methnum == 6 && !tog)
      return "TRACE cannot be controlled by <Limit>, see TraceEnable";

    if (methnum == 26)
      methnum = ap_method_register(cmd->pool, apr_pstrdup(cmd->pool, method));

    limited |= 1LL << methnum;
  }

  apr_int64_t v5 = tog ? ~limited : limited;

  if ((v5 & old_limited) == 0)
    return apr_pstrcat(cmd->pool, cmd->cmd->name, "> directive excludes all methods", 0LL);

  if ((v5 & old_limited) == old_limited)
    return apr_pstrcat(cmd->pool, cmd->cmd->name, "> directive specifies methods already excluded", 0LL);

  cmd->limited &= v5;
  const char *errmsg = ap_walk_config(cmd->directive->first_child, cmd, cmd->context);
  cmd->limited = old_limited;

  return errmsg;
}