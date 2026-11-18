int __cdecl compile_get_env(char_u **arg, cctx_T *cctx)
{
  char_u *name; // [rsp+0h] [rbp-30h]
  int ret; // [rsp+8h] [rbp-28h]
  int len; // [rsp+Ch] [rbp-24h]
  char_u *start; // [rsp+10h] [rbp-20h]

  start = (*arg)++;
  len = get_env_len(arg);
  if ( len )
  {
    name = vim_strnsave(start, len + 1);
    ret = generate_LOAD(cctx, ISN_LOADENV, 0, name, &t_string);
    vim_free(name);
    return ret;
  }
  else
  {
    semsg("E1002: Syntax error at %s", (const char *)start - 1);
    return 0;
  }
}