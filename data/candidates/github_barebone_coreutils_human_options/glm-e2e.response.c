int human_options(void *arg1, void *arg2, long long *arg3) {
    int ret;

    ret = humblock(arg1, arg3, arg2);
    
    if (*arg3 == 0) {
        *arg3 = default_block_size();
        ret = 4;
    }
    
    return ret;
}