int func0(long long int n, long long int *a) {
    int ret;
    *a ^= (1LL << n);
    ret = ((*a) > 0);
    return ret;
}