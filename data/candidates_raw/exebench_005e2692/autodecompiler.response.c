void SCE_Matrix2_MulV2 (SCE_TMatrix2 m, SCE_TVector2 v, SCE_TVector2 v2)
{
    v2[0] = m[0]*v[0] + m[2]*v[1];
    v2[1] = m[1]*v[0] + m[3]*v[1];
}