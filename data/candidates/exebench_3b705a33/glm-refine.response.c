void __cdecl mlCubicBezier(const float *p0, const float *p1, const float *p2, const float *p3, float t, float *v)
{
    // Calculate the 4 cubic Bezier basis functions (Bernstein polynomials)
    float u     = 1.0f - t;
    float tt    = t * t;
    float uu    = u * u;
    
    float b0    = uu * u;           // (1-t)^3
    float b1    = 3.0f * uu * t;    // 3(1-t)^2 * t
    float b2    = 3.0f * u * tt;    // 3(1-t) * t^2
    float b3    = tt * t;           // t^3

    // Interpolate the X, Y, and Z components
    v[0] = b0 * p0[0] + b1 * p1[0] + b2 * p2[0] + b3 * p3[0];
    v[1] = b0 * p0[1] + b1 * p1[1] + b2 * p2[1] + b3 * p3[1];
    v[2] = b0 * p0[2] + b1 * p1[2] + b2 * p2[2] + b3 * p3[2];
}