double frexp(double x, int *exp)
{
    double ret;
    int val, i, sign;

    sign = 1;
    if (x < 0.0) {
        sign = -1;
        x *= sign;
    } else if (x == 0.0) {
        *exp = 0;
        return 0.0;
    }

    *exp = 0;
    val = 1;
    ret = x;

    while (1) {
        if ((ret < 0.5) || (ret >= 1.0)) {
            val <<= 1;
            (*exp)++;
            ret = x / val;
        } else
            break;
    }
    ret *= sign;
    return ret;
}