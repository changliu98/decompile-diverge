char * ap_limit_section(cmd_parms *cmd,void *dummy,char *arg)

{
  void *pvVar1;
  ulong uVar2;
  apr_pool_t *p;
  char *pcVar3;
  ulong local_78;
  int methnum;
  char *method;
  char *errmsg;
  apr_int64_t old_limited;
  apr_int64_t limited;
  void *tog;
  char *limited_methods;
  char *endp;
  char *arg_local;
  void *dummy_local;
  cmd_parms *cmd_local;
  char *local_10;
  
  arg_local = arg;
  dummy_local = dummy;
  cmd_local = cmd;
  endp = strrchr(arg,0x3e);
  pvVar1 = cmd_local->cmd->cmd_data;
  limited = 0;
  uVar2 = cmd_local->limited;
  if (endp == (char *)0x0) {
    local_10 = unclosed_directive(cmd_local);
  }
  else {
    limited_methods = apr_pstrmemdup(cmd_local->temp_pool,arg_local,(long)endp - (long)arg_local);
    if (*limited_methods == '\0') {
      local_10 = missing_container_arg(cmd_local);
    }
    else {
      while (*limited_methods != '\0') {
        pcVar3 = ap_getword_conf(cmd_local->temp_pool,&limited_methods);
        methnum = ap_method_number_of(pcVar3);
        if ((methnum == 6) && (pvVar1 == (void *)0x0)) {
          local_10 = "TRACE cannot be controlled by <Limit>, see TraceEnable";
          return local_10;
        }
        if (methnum == 0x1a) {
          p = cmd_local->pool;
          pcVar3 = apr_pstrdup(cmd_local->pool,pcVar3);
          methnum = ap_method_register(p,pcVar3);
        }
        limited = 1L << ((byte)methnum & 0x3f) | limited;
      }
      if (pvVar1 == (void *)0x0) {
        local_78 = limited;
      }
      else {
        local_78 = limited ^ 0xffffffffffffffff;
      }
      if ((uVar2 & local_78) == 0) {
        local_10 = apr_pstrcat(cmd_local->pool,cmd_local->cmd->name,
                               "> directive excludes all methods",0);
      }
      else if ((uVar2 & local_78) == uVar2) {
        local_10 = apr_pstrcat(cmd_local->pool,cmd_local->cmd->name,
                               "> directive specifies methods already excluded",0);
      }
      else {
        cmd_local->limited = local_78 & cmd_local->limited;
        local_10 = ap_walk_config(cmd_local->directive->first_child,cmd_local,cmd_local->context);
        cmd_local->limited = uVar2;
      }
    }
  }
  return local_10;
}