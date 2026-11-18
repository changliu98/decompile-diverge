int
rational_best_approximation(unsigned long given_numerator,
                            unsigned long given_denominator,
                            unsigned long max_numerator,
                            unsigned long max_denominator,
                            unsigned long *best_numerator,
                            unsigned long *best_denominator)
{
    unsigned long n, d, n0, d0, n1, d1, n2, d2, q, r;

    n = given_numerator;
    d = given_denominator;
    n0 = 0;
    d0 = 1;
    n1 = 1;
    d1 = 0;

    while ((n1 <= max_numerator) && (d1 <= max_denominator)) {
        if (d == 0) {
            break;
        }
        q = n / d;
        r = n % d;
        n = d;
        d = r;
        n2 = q * n1 + n0;
        d2 = q * d1 + d0;
        n0 = n1;
        d0 = d1;
        n1 = n2;
        d1 = d2;
    }

    *best_numerator = n1;
    *best_denominator = d1;

    return 0;
}