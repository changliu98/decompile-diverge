void
mlCubicBezier(const float *p0, const float *p1, const float *p2, const float *p3, float t, float *v)
{
 v[0] = (1.0f - t) * (1.0f - t) *(1.0f - t) * p0[0] + 3.0f * (1.0f - t) * (1.0f - t) * t * p1[0] + 3.0f * (1.0f - t) * t * t * p2[0] + t * t * t * p3[0];
 v[1] = (1.0f - t) * (1.0f - t) *(1.0f - t) * p0[1] + 3.0f * (1.0f - t) * (1.0f - t) * t * p1[1] + 3.0f * (1.0f - t) * t * t * p2[1] + t * t * t * p3[1];
 v[2] = (1.0f - t) * (1.0f - t) *(1.0f - t) * p0[2] + 3.0f * (1.0f - t) * (1.0f - t) * t * p1[2] + 3.0f * (1.0f - t) * t * t * p2[2] + t * t * t * p3[2];
}