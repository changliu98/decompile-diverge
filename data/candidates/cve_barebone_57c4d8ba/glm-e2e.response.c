int compile_get_env(void **pp, void *arg2) {
    char *p = (char *)*pp;
    int ret;
    int len;
    char *saved_str;
    int gen_ret;

    // Advance the pointer pointed to by the first argument
    *pp = (void *)(p + 1);

    len = get_env_len(pp);
    if (len == 0) {
        semsg(e_syntax_error_at_str, p - 1);
        ret = 0;
    } else {
        saved_str = vim_strnsave(p, len + 1);
        gen_ret = generate_LOAD(arg2, saved_str, 0, t_string);
        vim_free(saved_str);
        ret = gen_ret;
    }

    return ret;
}