void af_filter_bilinear(float *a, float *b, float *k, float fs, float *coef)
{
    double na, nb;

    na = a[0] + a[1] * fs + a[2] * fs * fs;
    nb = b[0] + b[1] * fs + b[2] * fs * fs;

    *k = *k * (na / nb);

    coef[0] = (b[0] + 2.0 * b[0] - b[2] * fs * fs) / nb;
    coef[1] = (b[0] + b[2] * fs * fs - b[1] * fs) / nb;
    coef[2] = (a[0] + 2.0 * a[0] - a[2] * fs * fs) / na;
    coef[3] = (a[0] + a[2] * fs * fs - a[1] * fs) / na;
}