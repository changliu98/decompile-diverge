float getUniform(int a, int c, int m, float *x)
{
    *x = (a * *x + c) - m * (int)((a * *x + c) / m);
    *x = *x / m;

    return *x;
}