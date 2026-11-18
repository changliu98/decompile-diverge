void par_shapes__compute_normals(struct par_shapes_mesh* m)
{
 free(m->normals);
 m->normals = (float*)calloc(3 * m->num_vertices, sizeof(float));
 {
  float* n;
  float* p0;
  float* p1;
  float* p2;
  float c[3];
  float u[3];
  float v[3];
  unsigned short* t;
  int i;
  free(m->normals);
  m->normals = (float*)calloc(3 * m->num_vertices, sizeof(float));
  t = m->indices;
  for (i = 0;; i++, t += 3) {
   if (i >= m->num_triangles) {
    break;
   }
   p0 = &m->vertices[3 * t[0]];
   p1 = &m->vertices[3 * t[1]];
   p2 = &m->vertices[3 * t[2]];

   par_shapes__copy3(v, p1);
   par_shapes__subtract3(v, p0);
   par_shapes__copy3(u, p2);
   par_shapes__subtract3(u, p0);
   par_shapes__cross3(c, v, u);
   par_shapes__add3(&m->normals[3 * t[0]], c);

   par_shapes__copy3(v, p2);
   par_shapes__subtract3(v, p1);
   par_shapes__copy3(u, p0);
   par_shapes__subtract3(u, p1);
   par_shapes__cross3(c, v, u);
   par_shapes__add3(&m->normals[3 * t[1]], c);

   par_shapes__copy3(v, p0);
   par_shapes__subtract3(v, p2);
   par_shapes__copy3(u, p1);
   par_shapes__subtract3(u, p2);
   par_shapes__cross3(c, v, u);
   par_shapes__add3(&m->normals[3 * t[2]], c);
  }

  n = m->normals;
  for (i = 0;; i++, n += 3) {
   if (i >= m->num_vertices) {
    break;
   }
   par_shapes__normalize3(n);
  }
 }
}