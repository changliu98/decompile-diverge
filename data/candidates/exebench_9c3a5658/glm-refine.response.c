void __cdecl cmatrix_from_frame(matrix3x3 *m, const vec3 *v1, const vec3 *v2, const vec3 *v3)
{
    // Row 0
    m->m[0][0] = v1->x;
    m->m[0][1] = v2->x;
    m->m[0][2] = v3->x;

    // Row 1
    m->m[1][0] = v1->y;
    m->m[1][1] = v2->y;
    m->m[1][2] = v3->y;

    // Row 2
    m->m[2][0] = v1->z;
    m->m[2][1] = v2->z;
    m->m[2][2] = v3->z;
}