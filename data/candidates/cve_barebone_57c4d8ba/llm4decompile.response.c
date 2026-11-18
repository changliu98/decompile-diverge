int
compile_get_env(const char_u **expr, cctx_T *cctx)
{
    char_u *name;
    int len;
    int ret;
    char_u *start = *expr;

    /* Skip the '$' */
    (*expr)++;

    /* Get the length of the environment variable name */
    len = get_env_len(expr);
    if (len == 0)
    {
	semsg(e_syntax_error_at_str, start - 1);
	return 0;
    }

    /* Get the environment variable name */
    name = vim_strnsave(start, (size_t)(len + 1));

    /* Generate the code to get the environment variable */
    ret = generate_LOAD(cctx, ISN_LOADENV, 0, name, &t_string);

    vim_free(name);

    return ret;
}