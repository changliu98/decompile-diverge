void __cdecl par_shapes_compute_normals(par_shapes_mesh *m)
{
    int p, f;
    float *normal;
    float *pa, *pb, *pc;
    float cp[3];
    float edge1[3];
    float edge2[3];

    // Free any existing normals and allocate memory for the new normals array
    free(m->normals);
    m->normals = (float *)calloc(3 * sizeof(float) * m->npoints, 1uLL);

    // Accumulate normals for each vertex of each triangle
    for (f = 0; f < m->ntriangles; ++f)
    {
        const uint16_t i0 = m->triangles[f * 3 + 0];
        const uint16_t i1 = m->triangles[f * 3 + 1];
        const uint16_t i2 = m->triangles[f * 3 + 2];

        pa = &m->points[3 * i0];
        pb = &m->points[3 * i1];
        pc = &m->points[3 * i2];

        // Normal for vertex A (i0)
        par_shapes__copy3(edge1, pb);
        par_shapes__subtract3(edge1, pa);
        par_shapes__copy3(edge2, pc);
        par_shapes__subtract3(edge2, pa);
        par_shapes__cross3(cp, edge1, edge2);
        par_shapes__add3(&m->normals[3 * i0], cp);

        // Normal for vertex B (i1)
        par_shapes__copy3(edge1, pc);
        par_shapes__subtract3(edge1, pb);
        par_shapes__copy3(edge2, pa);
        par_shapes__subtract3(edge2, pb);
        par_shapes__cross3(cp, edge1, edge2);
        par_shapes__add3(&m->normals[3 * i1], cp);

        // Normal for vertex C (i2)
        par_shapes__copy3(edge1, pa);
        par_shapes__subtract3(edge1, pc);
        par_shapes__copy3(edge2, pb);
        par_shapes__subtract3(edge2, pc);
        par_shapes__cross3(cp, edge1, edge2);
        par_shapes__add3(&m->normals[3 * i2], cp);
    }

    // Normalize all accumulated normals
    normal = m->normals;
    for (p = 0; p < m->npoints; ++p)
    {
        par_shapes__normalize3(normal);
        normal += 3;
    }
}