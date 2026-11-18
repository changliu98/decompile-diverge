static void
KahanSummation(double y, double *compensation, double *last_sum,
               double *term, double *result)
{
    *term = y - *compensation;
    *result = *last_sum + *term;
    *compensation = (*result - *last_sum) - *term;
    *last_sum = *result;
}