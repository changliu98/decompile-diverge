00001

bool intersect_triangle1(
        const vec3 *orig,
        const vec3 *dir,
        const vec3 *vert0,
        const vec3 *vert1,
        const vec3 *vert2,
        double *t,
        double *u,
        double *v)
{
    vec3 edge1 = VEC_SUB(*vert1, *vert0);
    vec3 edge2 = VEC_SUB(*vert2, *vert0);
    
    vec3 pvec = VEC_CROSS(*dir, edge2);
    double det = VEC_DOT(edge1, pvec);

    // If the determinant is near zero, the ray lies in the plane of the triangle
    if (det > -EPSILON && det < EPSILON)
        return false;

    double inv_det = 1.0 / det;
    vec3 tvec = VEC_SUB(*orig, *vert0);

    // Calculate U parameter and test bounds
    *u = VEC_DOT(tvec, pvec);
    if (det > 0.0) {
        if (*u < 0.0 || *u > det)
            return false;
    } else {
        if (*u > 0.0 || *u < det)
            return false;
    }

    // Calculate V parameter and test bounds
    vec3 qvec = VEC_CROSS(tvec, edge1);
    *v = VEC_DOT(*dir, qvec);
    if (det > 0.0) {
        if (*v < 0.0 || *u + *v > det)
            return false;
    } else {
        if (*v > 0.0 || *u + *v < det)
            return false;
    }

    // Calculate T, scale U and V to their final values
    *t = VEC_DOT(edge2, qvec) * inv_det;
    *u *= inv_det;
    *v *= inv_det;

    return true;
}