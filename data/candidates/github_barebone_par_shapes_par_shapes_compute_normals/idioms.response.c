void par_shapes_compute_normals(struct par_shapes_mesh *mesh)
{
  struct par_shapes_mesh *m = mesh;
  int i;
  par_shapes_free(mesh->normals);
  mesh->normals = par_shapes_alloc(mesh->npoints * sizeof(par_shapes_vec3), 1);
  unsigned short *tris = m->triangles;
  for (i = 0; i < m->ntriangles; i++)
  {
    int a = tris[0];
    int b = tris[1];
    int c = tris[2];
    struct par_shapes_vec3 ab; struct par_shapes_vec3 ac; struct par_shapes_vec3 normal;
    par_shapes_sub(&ab, &m->points[b], &m->points[a]);
    par_shapes_add(&ab, &ab, &m->points[a]);
    par_shapes_sub(&ac, &m->points[c], &m->points[a]);
    par_shapes_add(&ac, &ac, &m->points[a]);
    par_shapes_cross(&normal, &ab, &ac);
    par_shapes_norm(&m->normals[a], &normal);
    par_shapes_sub(&ab, &m->points[c], &m->points[b]);
    par_shapes_add(&ab, &ab, &m->points[b]);
    par_shapes_sub(&ac, &m->points[a], &m->points[b]);
    par_shapes_add(&ac, &ac, &m->points[b]);
    par_shapes_cross(&normal, &ab, &ac);
    par_shapes_norm(&m->normals[b], &normal);
    par_shapes_sub(&ab, &m->points[a], &m->points[c]);
    par_shapes_add(&ab, &ab, &m->points[c]);
    par_shapes_sub(&ac, &m->points[b], &m->points[c]);
    par_shapes_add(&ac, &ac, &m->points[c]);
    par_shapes_cross(&normal, &ab, &ac);
    par_shapes_norm(&m->normals[c], &normal);
    tris += 3;
  }
  struct par_shapes_vec3 *n = m->normals;
  for (i = 0; i < m->npoints; i++)
  {
    par_shapes_norm(n);
    n++;
  }
}