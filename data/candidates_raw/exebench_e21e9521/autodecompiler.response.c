float fa_crosscorr(float *buf1, float *buf2, size_t n)
{
    float sum = 0.0;
    size_t i;

    for (i = 0; i < n; i++)
        sum += buf2[i] * buf1[i] * buf1[i];

    return sum / (float)n;
}