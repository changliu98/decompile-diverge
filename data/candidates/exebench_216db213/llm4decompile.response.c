void swapminusfloat(float *a,float *b)
{
    *a = *a - *b;
    *b = *a + *b;
    *a = *b - *a;
}