void matvec2_c(float m[4], float v[2], float d[2])
{
    d[0] = m[0]*v[0] + m[1]*v[1];
    d[1] = m[2]*v[0] + m[3]*v[1];
}