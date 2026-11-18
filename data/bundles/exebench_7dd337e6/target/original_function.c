extern void _kahan_summation_step(
    double new_value, double *sum, double *err, double *loc, double *tmp)
{
    *loc = new_value - *err;
    *tmp = *sum + *loc;
    *err = (*tmp - *sum) - *loc;
    *sum = *tmp;
}