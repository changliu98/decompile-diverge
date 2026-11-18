void geom_matvec3f( const float *m, const vec3_t in, vec3_t out )
{
 out[0] = m[0] * in[0] + m[3] * in[1] + m[6] * in[2];
 out[1] = m[1] * in[0] + m[4] * in[1] + m[7] * in[2];
 out[2] = m[2] * in[0] + m[5] * in[1] + m[8] * in[2];
}