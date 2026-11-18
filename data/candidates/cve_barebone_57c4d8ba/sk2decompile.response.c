static int compile_get_env(char_u **p_ptr, lex_env_T *env) {
  char_u *p;
  int len;
  int ret;
  p = *p_ptr;
  (*p_ptr)++;
  len = get_env_len(p_ptr);
  if (len == 0) {
    semsg("E1002: Syntax error at %s", p - 1);
    return 0;
  }
  p = vim_strnsave(p, len + 1);
  ret = generate_LOAD(env, OP_GETENV, 0, p, &zero_addr);
  vim_free(p);
  return ret;
}