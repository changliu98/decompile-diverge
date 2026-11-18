int intersect_triangle(const double *orig, const double *dir,
                       const double *v0, const double *v1, const double *v2,
                       double *t, double *u, double *v) {
    double edge1[3];
    double edge2[3];
    double pvec[3];
    double qvec[3];
    double tvec[3];
    double det;
    double inv_det;

    // edge1 = v1 - v0
    edge1[0] = v1[0] - v0[0];
    edge1[1] = v1[1] - v0[1];
    edge1[2] = v1[2] - v0[2];

    // edge2 = v2 - v0
    edge2[0] = v2[0] - v0[0];
    edge2[1] = v2[1] - v0[1];
    edge2[2] = v2[2] - v0[2];

    // pvec = cross(dir, edge2)
    pvec[0] = dir[1] * edge2[2] - dir[2] * edge2[1];
    pvec[1] = dir[2] * edge2[0] - dir[0] * edge2[2];
    pvec[2] = dir[0] * edge2[1] - dir[1] * edge2[0];

    // det = dot(edge1, pvec)
    det = edge1[0] * pvec[0] + edge1[1] * pvec[1] + edge1[2] * pvec[2];

    // Culling branch: if determinant is too close to zero, ray lies in plane of triangle
    if (det <= 1e-8 || det >= -1e-8) {
        return 0;
    }

    inv_det = 1.0 / det;

    // tvec = orig - v0
    tvec[0] = orig[0] - v0[0];
    tvec[1] = orig[1] - v0[1];
    tvec[2] = orig[2] - v0[2];

    // u = dot(tvec, pvec) * inv_det
    *u = (tvec[0] * pvec[0] + tvec[1] * pvec[1] + tvec[2] * pvec[2]) * inv_det;

    // Check bounds for u
    if (*u < 0.0 || *u > 1.0) {
        return 0;
    }

    // qvec = cross(tvec, edge1)
    qvec[0] = tvec[1] * edge1[2] - tvec[2] * edge1[1];
    qvec[1] = tvec[2] * edge1[0] - tvec[0] * edge1[2];
    qvec[2] = tvec[0] * edge1[1] - tvec[1] * edge1[0];

    // v = dot(dir, qvec) * inv_det
    *v = (dir[0] * qvec[0] + dir[1] * qvec[1] + dir[2] * qvec[2]) * inv_det;

    // Check bounds for v and that u + v <= 1
    if (*v < 0.0 || *u + *v > 1.0) {
        return 0;
    }

    // t = dot(edge2, qvec) * inv_det
    *t = (edge2[0] * qvec[0] + edge2[1] * qvec[1] + edge2[2] * qvec[2]) * inv_det;

    return 1;
}