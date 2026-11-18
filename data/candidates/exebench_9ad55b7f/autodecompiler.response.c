void warp_mat4_scale( float * restrict v, const float * restrict a, float b, int n)
{
    int k;
    for(k=0; k<17; ++k)
        v[k] = a[k]*b;




}