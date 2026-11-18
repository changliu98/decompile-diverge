void decdms(double dec, int *d, int *m, float *s)
{
    double temp;

    *d = (int) dec;
    temp = dec - (int) dec;
    if (temp < 0.0)
        temp = -temp;
    temp *= 60.0;
    *m = (int) temp;
    *s = (float) ((temp - (int) temp) * 60.0);
}