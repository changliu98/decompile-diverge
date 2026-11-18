static int zuchk_(const double *a, const double *b, int *sign,
                         const double *tol, const double *max_rel_err)
{
    double abs_err, abs_err_b, max_abs_err, rel_err;
    int ret;

    *sign = 0;
    if (*a >= 0) {
        max_abs_err = *a;
    } else {
        max_abs_err = -*a;
    }
    abs_err_b = max_abs_err;
    if (*b >= 0) {
        max_abs_err = *b;
    } else {
        max_abs_err = -*b;
    }
    abs_err = max_abs_err;
    if (abs_err_b > max_abs_err)
        max_abs_err = abs_err_b;
    if (max_abs_err > *tol) {
        ret = 0;
    } else {
        if (abs_err <= abs_err_b) {
            rel_err = abs_err / abs_err_b;
        } else {
            rel_err = abs_err_b / abs_err;
        }
        if (rel_err > *max_rel_err) {
            *sign = 1;
            ret = 0;
        } else {
            ret = 1;
        }
    }
    return ret;
}