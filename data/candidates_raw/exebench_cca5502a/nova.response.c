int func0(float *out, int *out_len, int *x, int *y, float *tmp) {
    int ret;
    if (*out_len == 1) {
        *out = *y;
        ret = 1;
    } else if (*out_len > *x) {
        *out = *y;
        *x = *out_len;
        tmp[*out_len - 1] = *y;
        ret = 1;
    } else if (*out_len > 1) {
        *out = tmp[*out_len - 1];
        ret = 0;
    } else {
        ret = 0;
    }
    return ret;
}