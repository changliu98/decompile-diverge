double icvDotProduct_32f( const float* a, const float* b, int len )
{
    double result = 0;
    int i;

    for( i = 0; i < len; i++ )
        result += a[i] * b[i];

    return result;
}