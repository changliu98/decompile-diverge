void __cdecl mlQuadBezier(const float *p0, const float *p1, const float *p2, float t, float *v)
{
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float u_t = 2.0f * u * t;

    v[0] = uu * p0[0] + u_t * p1[0] + tt * p2[0];
    v[1] = uu * p0[1] + u_t * p1[1] + tt * p2[1];
    v[2] = uu * p0[2] + u_t * p1[2] + tt * p2[2];
}