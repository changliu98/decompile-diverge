void mlQuadBezier(vec3 *p0, vec3 *p1, vec3 *p2, float t, vec3 *out) {
    float u = 1.0f - t;
    float t2 = t * t;
    float u2 = u * u;
    float ut2 = 2.0f * u * t;

    out->x = u2 * p0->x + ut2 * p1->x + t2 * p2->x;
    out->y = u2 * p0->y + ut2 * p1->y + t2 * p2->y;
    out->z = u2 * p0->z + ut2 * p1->z + t2 * p2->z;
}