int
get_link(float *y, int *k, int *n, float *x, float *l)
{
    int ret;

    if (*k == 1) {
 *y = *x;
 ret = 1;
    }
    else if (*k > *n) {
 *y = *x;
 *n = *k;
 l[*k - 2] = *x;
 ret = 1;
    }
    else if (*k > 1) {
 *y = l[*k - 2];
 ret = 0;
    }
    else
 ret = 0;
    return(ret);
}