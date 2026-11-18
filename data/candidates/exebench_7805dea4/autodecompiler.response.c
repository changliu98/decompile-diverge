void mlVectorMultMatrixTo(float v[3], float m[16], float d[3])
{
    d[0] = m[0] * v[0] + m[4] * v[1] + m[8 ] * v[2] + m[12];
    d[1] = m[1] * v[0] + m[5] * v[1] + m[9 ] * v[2] + m[13];
    d[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];
}