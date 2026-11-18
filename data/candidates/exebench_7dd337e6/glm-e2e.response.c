void _kahan_summation_step(double input, double *sum, double *c, double *y) {
    *y = input - *c;
    *sum = *sum + *y;
    *c = (*sum - *sum) - *y; // Note: This appears to be a compiler optimization bug or an intentional quirk in the original code.
    *sum = *sum;
}