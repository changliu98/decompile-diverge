double GO_frexp(double x, int *eptr) {
    double ret;
    int e;

    e = 0;
    ret = 0.0;
    if (x < 0.0) {
        x = -x;
    }
    if (x!= 0.0) {
        if (x >= DBL_MIN) {
            while (x < HALF) {
                e -= 1;
                x *= TWO;
            }
            while (x >= TWO) {
                e += 1;
                x *= ONE_HALF;
            }
        } else {
            while (x < HALF) {
                e -= 1;
                x *= TWO;
            }
        }
        ret = x;
    }
    *eptr = e;
    return (ret * TWO);
}