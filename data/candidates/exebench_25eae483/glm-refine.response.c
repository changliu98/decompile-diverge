int __cdecl intersect_triangle(
        double *orig,
        double *dir,
        double *vert0,
        double *vert1,
        double *vert2,
        double *t,
        double *u,
        double *v)
{
    double edge1[3];
    double edge2[3];
    double pvec[3];
    double tvec[3];
    double qvec[3];
    double det;
    double inv_det;

    // Find vectors for two edges sharing vert0
    edge1[0] = vert1[0] - vert0[0];
    edge1[1] = vert1[1] - vert0[1];
    edge1[2] = vert1[2] - vert0[2];

    edge2[0] = vert2[0] - vert0[0];
    edge2[1] = vert2[1] - vert0[1];
    edge2[2] = vert2[2] - vert0[2];

    // Begin calculating determinant - also used to calculate U parameter
    cross_product(pvec, dir, edge2);

    // If determinant is near zero, ray lies in plane of triangle
    det = dot_product(edge1, pvec);
    if (det > -0.000001 && det < 0.000001)
        return 0;
    
    inv_det = 1.0 / det;

    // Calculate distance from vert0 to ray origin
    tvec[0] = orig[0] - vert0[0];
    tvec[1] = orig[1] - vert0[1];
    tvec[2] = orig[2] - vert0[2];

    // Calculate U parameter and test bounds
    *u = dot_product(tvec, pvec) * inv_det;
    if (*u < 0.0 || *u > 1.0)
        return 0;

    // Prepare to test V parameter
    cross_product(qvec, tvec, edge1);

    // Calculate V parameter and test bounds
    *v = dot_product(dir, qvec) * inv_det;
    if (*v < 0.0 || *u + *v > 1.0)
        return 0;

    // Calculate T, ray intersection distance
    *t = dot_product(edge2, qvec) * inv_det;

    return 1;
}