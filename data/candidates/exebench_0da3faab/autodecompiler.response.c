void mac_real (SCE_TVector2 v, float *a, SCE_TVector2 w)
{
    w[0] += v[0]*(*a);
    w[1] += v[1]*(*a);
}