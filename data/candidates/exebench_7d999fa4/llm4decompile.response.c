int bkm_scale(bkm_data *x, int scale_factor)
{
    int ret;
    if (x->mantissa * (long long)scale_factor / scale_factor == x->mantissa) {
        x->mantissa *= scale_factor;
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}