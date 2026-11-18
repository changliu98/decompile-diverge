static __inline const char *func0(const char *fname) {
    static char buf[3569];
    struct __rpc_sockinfo si;
    int ret;
    const char *ret_fn;

    __rpc_sockinfo_get(&si, (const char *)fname, 1);
    ret = __rpc_pipe_connect3(&si, fname, 0, 0);
    if (ret == 0)
        ret_fn = "(null)";
    else
        ret_fn = "(nonnull)";
    __rpc_sockinfo_put(&si);
    return ret_fn;
}