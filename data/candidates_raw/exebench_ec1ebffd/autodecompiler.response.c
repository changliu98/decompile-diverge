int __attribute__((visibility("default"))) x86_compare (float *x, float *y, int n)
{
    int i;
    int ret;

    if (!x || !y) {
        ret = 1;
        goto end;
    }

    for (i = 0; i < n; i++) {
        if (x[i] > y[i]) {
            ret = 0;
            goto end;
        }
    }

    ret = 1;

end:
    return ret;
}