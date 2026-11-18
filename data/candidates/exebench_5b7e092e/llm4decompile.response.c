void mlQuadBezier(float p0[3], float p1[3], float p2[3], float t, float v[3])
{
 float B0 = (1 - t) * (1 - t);
 float B1 = 2 * t * (1 - t);
 float B2 = t * t;

 v[0] = B0 * p0[0] + B1 * p1[0] + B2 * p2[0];
 v[1] = B0 * p0[1] + B1 * p1[1] + B2 * p2[1];
 v[2] = B0 * p0[2] + B1 * p1[2] + B2 * p2[2];
}