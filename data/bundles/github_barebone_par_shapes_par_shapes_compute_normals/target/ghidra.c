void par_shapes_compute_normals(par_shapes_mesh *m)

{
  float *pfVar1;
  float *a;
  float *a_00;
  int p;
  float *normal;
  float *pc;
  float *pb;
  float *pa;
  int f;
  float cp [3];
  float prev [3];
  float next [3];
  uint16_t *triangle;
  par_shapes_mesh *m_local;
  
  free(m->normals);
  pfVar1 = calloc((long)(m->npoints * 3) << 2,1);
  m->normals = pfVar1;
  triangle = m->triangles;
  for (f = 0; f < m->ntriangles; f = f + 1) {
    pfVar1 = m->points + (int)((uint)*triangle * 3);
    a = m->points + (int)((uint)triangle[1] * 3);
    a_00 = m->points + (int)((uint)triangle[2] * 3);
    par_shapes__copy3(next,a);
    par_shapes__subtract3(next,pfVar1);
    par_shapes__copy3(prev,a_00);
    par_shapes__subtract3(prev,pfVar1);
    par_shapes__cross3(cp,next,prev);
    par_shapes__add3(m->normals + (int)((uint)*triangle * 3),cp);
    par_shapes__copy3(next,a_00);
    par_shapes__subtract3(next,a);
    par_shapes__copy3(prev,pfVar1);
    par_shapes__subtract3(prev,a);
    par_shapes__cross3(cp,next,prev);
    par_shapes__add3(m->normals + (int)((uint)triangle[1] * 3),cp);
    par_shapes__copy3(next,pfVar1);
    par_shapes__subtract3(next,a_00);
    par_shapes__copy3(prev,a);
    par_shapes__subtract3(prev,a_00);
    par_shapes__cross3(cp,next,prev);
    par_shapes__add3(m->normals + (int)((uint)triangle[2] * 3),cp);
    triangle = triangle + 3;
  }
  normal = m->normals;
  for (p = 0; p < m->npoints; p = p + 1) {
    par_shapes__normalize3(normal);
    normal = normal + 3;
  }
  return;
}