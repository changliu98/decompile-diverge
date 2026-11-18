int dummywc_mbtowc(int *pwc, const char *s, size_t n) {
    int ret;
    
    if (n > 0 && *s != 0) {
        *pwc = (signed char)*s;
        ret = 1;
    } else {
        ret = 0;
    }
    
    return ret;
}