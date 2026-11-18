void par_shapes_compute_normals(par_shapes_mesh *m)
{
    int i;
    float *normals;
    float *n;
    float *p0, *p1, *p2;
    float e1[3], e2[3], cp[3];
    uint16_t *triangle;

    free(m->normals);
    m->normals = calloc((size_t)(m->npoints * 3), sizeof(float));
    triangle = m->triangles;
    normals = m->normals;
    for (i = 0; i < m->ntriangles; i++, triangle += 3) {
        p0 = m->points + 3 * triangle[0];
        p1 = m->points + 3 * triangle[1];
        p2 = m->points + 3 * triangle[2];

        par_shapes__copy3(e1, p1);
        par_shapes__subtract3(e1, p0);
        par_shapes__copy3(e2, p2);
        par_shapes__subtract3(e2, p0);
        par_shapes__cross3(cp, e1, e2);
        par_shapes__add3(normals + 3 * triangle[0], cp);

        par_shapes__copy3(e1, p2);
        par_shapes__subtract3(e1, p1);
        par_shapes__copy3(e2, p0);
        par_shapes__subtract3(e2, p1);
        par_shapes__cross3(cp, e1, e2);
        par_shapes__add3(normals + 3 * triangle[1], cp);

        par_shapes__copy3(e1, p0);
        par_shapes__subtract3(e1, p2);
        par_shapes__copy3(e2, p1);
        par_shapes__subtract3(e2, p2);
        par_shapes__cross3(cp, e1, e2);
        par_shapes__add3(normals + 3 * triangle[2], cp);
    }

    n = m->normals;
    for (i = 0; i < m->npoints; i++, n += 3) {
        par_shapes__normalize3(n);
    }
}