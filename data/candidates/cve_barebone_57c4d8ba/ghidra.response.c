int compile_get_env(char_u **arg,cctx_T *cctx)

{
  int iVar1;
  char_u *pcVar2;
  char_u *name;
  int ret;
  int len;
  char_u *start;
  cctx_T *cctx_local;
  char_u **arg_local;
  int local_c;
  
  pcVar2 = *arg;
  *arg = *arg + 1;
  iVar1 = get_env_len(arg);
  if (iVar1 == 0) {
    semsg(e_syntax_error_at_str,pcVar2 + -1);
    local_c = 0;
  }
  else {
    pcVar2 = vim_strnsave(pcVar2,(long)(iVar1 + 1));
    local_c = generate_LOAD(cctx,ISN_LOADENV,0,pcVar2,&t_string);
    vim_free(pcVar2);
  }
  return local_c;
}