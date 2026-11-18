static int
compile_get_env(
    char_u **pp,
    context_t *cctx)
{
    int len;
    char_u *p;
    char_u *env;
    int ret;

    p = *pp;
    ++*pp;

    len = get_env_len(pp);
    if (len == 0)
    {
 semsg((char_u *)"E1002: Syntax error at %s", p - 1);
 ret = 0;
    }
    else
    {
 env = vim_strnsave(p, len + 1);
 ret = generate_LOAD(cctx, NULL, NULL, env, &t_string);
 vim_free(env);
    }

    return ret;
}