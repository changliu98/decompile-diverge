double func0(int64_t *x) {
    int64_t i;
    double d;

    i = *x / I;
    *x = CONG * (*x - i * I) - K * i;
    if (*x < 0)
        *x += IM;
    d = (double)*x * ONE_PCT;
    return d;
}