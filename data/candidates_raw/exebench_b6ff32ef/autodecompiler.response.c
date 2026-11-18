void SCE_Matrix3_MulV3Copy (SCE_TMatrix3 m, const SCE_TVector3 v)
{
    float t[2];
    t[0] = m[0]*v[0] + m[1]*v[2];
    t[1] = m[2]*v[0] + m[3]*v[2];
    float tz = m[4]*v[0] + m[5]*v[2] + v[4];
    m[1] = m[0]*v[1] + m[1]*v[3];
    m[3] = m[2]*v[1] + m[3]*v[3];
    m[5] = m[4]*v[1] + m[5]*v[3] + v[5];
    m[0] = t[0];
    m[2] = t[1];
    m[4] = tz;
}