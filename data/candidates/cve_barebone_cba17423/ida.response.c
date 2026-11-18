const char *__cdecl ap_limit_section(cmd_parms *cmd, void *dummy, const char *arg)
{
  char *v3; // rax
  apr_int64_t v5; // [rsp+0h] [rbp-70h]
  apr_pool_t *p; // [rsp+8h] [rbp-68h]
  int methnum; // [rsp+14h] [rbp-5Ch]
  const char *method; // [rsp+18h] [rbp-58h]
  const char *errmsg; // [rsp+20h] [rbp-50h]
  apr_int64_t old_limited; // [rsp+28h] [rbp-48h]
  apr_int64_t limited; // [rsp+30h] [rbp-40h]
  void *tog; // [rsp+38h] [rbp-38h]
  const char *limited_methods; // [rsp+40h] [rbp-30h] BYREF
  const char *endp; // [rsp+48h] [rbp-28h]
  const char *arga; // [rsp+50h] [rbp-20h]
  void *dummya; // [rsp+58h] [rbp-18h]
  cmd_parms *cmda; // [rsp+60h] [rbp-10h]

  cmda = cmd;
  dummya = dummy;
  arga = arg;
  endp = strrchr(arg, 62);
  tog = cmd->cmd->cmd_data;
  limited = 0LL;
  old_limited = cmd->limited;
  if ( !endp )
    return unclosed_directive(cmda);
  limited_methods = apr_pstrmemdup(cmda->temp_pool, arga, endp - arga);
  if ( !*limited_methods )
    return missing_container_arg(cmda);
  while ( *limited_methods )
  {
    method = ap_getword_conf(cmda->temp_pool, &limited_methods);
    methnum = ap_method_number_of(method);
    if ( methnum == 6 && !tog )
      return "TRACE cannot be controlled by <Limit>, see TraceEnable";
    if ( methnum == 26 )
    {
      p = cmda->pool;
      v3 = apr_pstrdup(p, method);
      LOBYTE(methnum) = ap_method_register(p, v3);
    }
    limited |= 1LL << methnum;
  }
  if ( tog )
    v5 = ~limited;
  else
    v5 = limited;
  if ( (v5 & old_limited) == 0 )
    return apr_pstrcat(cmda->pool, cmda->cmd->name, "> directive excludes all methods", 0LL);
  if ( (v5 & old_limited) == old_limited )
    return apr_pstrcat(cmda->pool, cmda->cmd->name, "> directive specifies methods already excluded", 0LL);
  cmda->limited &= v5;
  errmsg = ap_walk_config(cmda->directive->first_child, cmda, cmda->context);
  cmda->limited = old_limited;
  return errmsg;
}