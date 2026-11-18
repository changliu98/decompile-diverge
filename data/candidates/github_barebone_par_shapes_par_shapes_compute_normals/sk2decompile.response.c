static void par_shapes_compute_normals(par_shapes_mesh *mesh) {
  int i, j;
  float *n, *a, *b, *c, *da, *db;
  const unsigned short *tri;
  float nn[3], ab[3], bc[3];
  par_shapes_mesh *m = mesh;
  free(m->normals);
  m->normals = (float *)calloc(3 * m->npoints, sizeof(float));
  tri = m->triangles;
  for (j = 0; j < m->ntriangles; ++j) {
    n = m->normals + 3 * tri[0];
    a = m->normals + 3 * tri[1];
    b = m->normals + 3 * tri[2];
    c = m->points + 3 * tri[0];
    da = m->points + 3 * tri[1];
    db = m->points + 3 * tri[2];
    par_shapes__copy3(ab, a);
    par_shapes__subtract3(ab, c);
    par_shapes__copy3(bc, b);
    par_shapes__subtract3(bc, c);
    par_shapes__cross3(nn, ab, bc);
    par_shapes__add3(n, nn);
    par_shapes__copy3(ab, b);
    par_shapes__subtract3(ab, a);
    par_shapes__copy3(bc, c);
    par_shapes__subtract3(bc, a);
    par_shapes__cross3(nn, ab, bc);
    par_shapes__add3(a, nn);
    par_shapes__copy3(ab, c);
    par_shapes__subtract3(ab, b);
    par_shapes__copy3(bc, a);
    par_shapes__subtract3(bc, b);
    par_shapes__cross3(nn, ab, bc);
    par_shapes__add3(b, nn);
    tri += 3;
  }
  n = m->normals;
  for (i = 0; i < m->npoints; ++i) {
    par_shapes__normalize3(n);
    n += 3;
  }
}