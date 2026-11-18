void mlCubicBezier(const Vec3 *p0, const Vec3 *p1, const Vec3 *p2, const Vec3 *p3, float t, Vec3 *out) {
    float u = 1.0f - t;
    float uu = u * u;
    float uuu = uu * u;
    float tt = t * t;
    float ttt = tt * t;

    // The assembly uses the expanded form of the cubic Bezier formula:
    // P(t) = P0*(1-t)^3 + 3*P1*t*(1-t)^2 + 3*P2*t^2*(1-t) + P3*t^3
    // which is algebraically equivalent to:
    // P(t) = P0*(1-t)^3 + P1*(3t - 6t^2 + 3t^3) + P2*(3t^2 - 3t^3) + P3*t^3

    out->x = p0->x * uuu +
             p1->x * (3.0f * t * u * u) +
             p2->x * (3.0f * tt * u) +
             p3->x * ttt;

    out->y = p0->y * uuu +
             p1->y * (3.0f * t * u * u) +
             p2->y * (3.0f * tt * u) +
             p3->y * ttt;

    out->z = p0->z * uuu +
             p1->z * (3.0f * t * u * u) +
             p2->z * (3.0f * tt * u) +
             p3->z * ttt;
}