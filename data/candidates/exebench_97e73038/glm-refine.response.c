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
    // 1. Unpack pointers into 3D vectors for readability
    vec3 O = { orig[0], orig[1], orig[2] };
    vec3 D = { dir[0],  dir[1],  dir[2]  };
    vec3 V0 = { vert0[0], vert0[1], vert0[2] };
    vec3 V1 = { vert1[0], vert1[1], vert1[2] };
    vec3 V2 = { vert2[0], vert2[1], vert2[2] };

    // 2. Find vectors for two edges sharing vert0
    vec3 edge1 = { V1.x - V0.x, V1.y - V0.y, V1.z - V0.z };
    vec3 edge2 = { V2.x - V0.x, V2.y - V0.y, V2.z - V0.z };

    // 3. Begin calculating determinant - also used to calculate U parameter
    // pvec = cross(dir, edge2)
    vec3 pvec = {
        D.y * edge2.z - D.z * edge2.y,
        D.z * edge2.x - D.x * edge2.z,
        D.x * edge2.y - D.y * edge2.x
    };

    // 4. If determinant is near zero, ray lies in plane of triangle
    // det = dot(edge1, pvec)
    double det = edge1.x * pvec.x + edge1.y * pvec.y + edge1.z * pvec.z;
    if (det < 0.000001)
        return 0;

    // 5. Calculate distance from vert0 to ray origin
    vec3 tvec = { O.x - V0.x, O.y - V0.y, O.z - V0.z };

    // 6. Calculate U parameter and test bounds
    // *u = dot(tvec, pvec)
    *u = tvec.x * pvec.x + tvec.y * pvec.y + tvec.z * pvec.z;
    if (*u < 0.0 || *u > det)
        return 0;

    // 7. Prepare to test V parameter
    // qvec = cross(tvec, edge1)
    vec3 qvec = {
        tvec.y * edge1.z - tvec.z * edge1.y, // Reconstructed missing qvec[0]
        tvec.z * edge1.x - tvec.x * edge1.z,
        tvec.x * edge1.y - tvec.y * edge1.x
    };

    // 8. Calculate V parameter and test bounds
    // *v = dot(dir, qvec)
    *v = D.x * qvec.x + D.y * qvec.y + D.z * qvec.z;
    if (*v < 0.0 || *u + *v > det)
        return 0;

    // 9. Calculate t, scale parameters, and test if ray intersects triangle
    // *t = dot(edge2, qvec)
    *t = edge2.x * qvec.x + edge2.y * qvec.y + edge2.z * qvec.z;
    
    // Original logic preserves division order: (1.0 / det) * *t
    double inv_det = 1.0 / det;
    *t = inv_det * *t;
    *u = inv_det * *u;
    *v = inv_det * *v;

    return 1;
}