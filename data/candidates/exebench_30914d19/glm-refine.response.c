void __cdecl rsVec_cross(float *v, float *vec1, float *vec2)
{
    v[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    v[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    v[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}