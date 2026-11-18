void vec_scaledxy_add(double s1, double *v1, double s2, double *v2, double *v3)
{
    v3[0] = s1*v1[0] + s2*v2[0];
    v3[1] = s1*v1[1] + s2*v2[1];
    v3[2] = s1*v1[2] + s2*v2[2];
}