int compile_get_env(char **s, struct cctx_T *ctx)
{
  char *name;
  int len;
  int ret;
  name = *s;
  (*s)++;
  len = iset_get_name(s);
  if (len == 0)
  {
    iset_error("E1002: Syntax error at %s", name - 1);
    return (0);
  }
  name = iset_get_str(name, len + 1);
  ret = iset_call(ctx, ISN_LOADENV, 0, name, &t_string);
  iset_free(name);
  return (ret);
}