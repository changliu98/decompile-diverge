int func0(int *ptr, int old, int new) {
    int ret = *ptr;
    *ptr = new;
    return ret;
}