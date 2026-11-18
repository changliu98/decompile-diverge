static double icvDotProduct_32f( const float* src1, const float* src2, int len )
{
    double s = 0;
    for( int i = 0; i < len; i++ ) s += src1[i]*src2[i];

    ;

    return s;
}