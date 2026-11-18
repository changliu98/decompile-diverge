int intersect_triangle(const vec3 *orig, const vec3 *dir,
                       const vec3 *v0, const vec3 *v1, const vec3 *v2,
                       double *t, double *u, double *v) {
    vec3 edge1, edge2;
    vec3 tvec, pvec, qvec;
    double det, inv_det;

    edge1.x = v1->x - v0->x;
    edge1.y = v1->y - v0->y;
    edge1.z = v1->z - v0->z;

    edge2.x = v2->x - v0->x;
    edge2.y = v2->y - v0->y;
    edge2.z = v2->z - v0->z;

    pvec.x = dir->y * edge2.z - dir->z * edge2.y;
    pvec.y = dir->z * edge2.x - dir->x * edge2.z;
    pvec.z = dir->x * edge2.y - dir->y * edge2.x;

    det = edge1.x * pvec.x + edge1.y * pvec.y + edge1.z * pvec.z;

    if (det > -1e-8 && det < 1e-8)
        return 0;

    inv_det = 1.0 / det;

    tvec.x = orig->x - v0->x;
    tvec.y = orig->y - v0->y;
    tvec.z = orig->z - v0->z;

    *u = (tvec.x * pvec.x + tvec.y * pvec.y + tvec.z * pvec.z) * inv_det;
    if (*u < 0.0 || *u > 1.0)
        return 0;

    qvec.x = tvec.y * edge1.z - tvec.z * edge1.y;
    qvec.y = tvec.z * edge1.x - tvec.x * edge1.z;
    qvec.z = tvec.x * edge1.y - tvec.y * edge1.x;

    *v = (dir->x * qvec.x + dir->y * qvec.y + dir->z * qvec.z) * inv_det;
    if (*v < 0.0 || *u + *v > 1.0)
        return 0;

    *t = (edge2.x * qvec.x + edge2.y * qvec.y + edge2.z * qvec.z) * inv_det;

    return 1;
}