#include <math.h>

#include <stdio.h>

#include <string.h>

void
mlQuadBezier(const float *p0, const float *p1, const float *p2, float t, float *v)
{
 v[0] = (1.0f - t) * (1.0f - t) * p0[0] + 2.0f * (1.0f - t) * t * p1[0] + t * t * p2[0];
 v[1] = (1.0f - t) * (1.0f - t) * p0[1] + 2.0f * (1.0f - t) * t * p1[1] + t * t * p2[1];
 v[2] = (1.0f - t) * (1.0f - t) * p0[2] + 2.0f * (1.0f - t) * t * p1[2] + t * t * p2[2];
}
