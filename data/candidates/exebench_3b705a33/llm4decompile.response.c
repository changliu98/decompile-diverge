void mlCubicBezier(float p0[3], float p1[3], float p2[3], float p3[3], float t, float v[3])
{
 float B0 = (1 - t) * (1 - t) * (1 - t);
 float B1 = 3 * t * (1 - t) * (1 - t);
 float B2 = 3 * t * t * (1 - t);
 float B3 = t * t * t;

 v[0] = B0 * p0[0] + B1 * p1[0] + B2 * p2[0] + B3 * p3[0];
 v[1] = B0 * p0[1] + B1 * p1[1] + B2 * p2[1] + B3 * p3[1];
 v[2] = B0 * p0[2] + B1 * p1[2] + B2 * p2[2] + B3 * p3[2];
}