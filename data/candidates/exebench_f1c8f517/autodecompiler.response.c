void ml_multiply_mat4_vec4( const float m[16], const float v[4], float d[4] )
{
 float tmp[4];

 tmp[0] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3];
 tmp[1] = m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7] * v[3];
 tmp[2] = m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11] * v[3];
 tmp[3] = m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3];

 d[0] = tmp[0];
 d[1] = tmp[1];
 d[2] = tmp[2];
 d[3] = tmp[3];
}