void vec_dot_prod(int n, double *x, double *y, double *z)
{
    do {
        *y++ += (*z++) * (*x++);
    } while (--n);
}