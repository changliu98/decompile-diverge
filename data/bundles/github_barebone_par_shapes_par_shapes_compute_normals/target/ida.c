void __cdecl par_shapes_compute_normals(par_shapes_mesh *m)
{
  int p; // [rsp+4h] [rbp-5Ch]
  float *normal; // [rsp+8h] [rbp-58h]
  float *pc; // [rsp+10h] [rbp-50h]
  float *pb; // [rsp+18h] [rbp-48h]
  float *pa; // [rsp+20h] [rbp-40h]
  int f; // [rsp+28h] [rbp-38h]
  float cp[3]; // [rsp+2Ch] [rbp-34h] BYREF
  float prev[3]; // [rsp+38h] [rbp-28h] BYREF
  float next[3]; // [rsp+44h] [rbp-1Ch] BYREF
  const uint16_t *triangle; // [rsp+50h] [rbp-10h]
  par_shapes_mesh *ma; // [rsp+58h] [rbp-8h]

  ma = m;
  free(m->normals);
  m->normals = (float *)calloc(12LL * m->npoints, 1uLL);
  triangle = ma->triangles;
  for ( f = 0; f < ma->ntriangles; ++f )
  {
    pa = &ma->points[3 * *triangle];
    pb = &ma->points[3 * triangle[1]];
    pc = &ma->points[3 * triangle[2]];
    par_shapes__copy3(next, pb);
    par_shapes__subtract3(next, pa);
    par_shapes__copy3(prev, pc);
    par_shapes__subtract3(prev, pa);
    par_shapes__cross3(cp, next, prev);
    par_shapes__add3(&ma->normals[3 * *triangle], cp);
    par_shapes__copy3(next, pc);
    par_shapes__subtract3(next, pb);
    par_shapes__copy3(prev, pa);
    par_shapes__subtract3(prev, pb);
    par_shapes__cross3(cp, next, prev);
    par_shapes__add3(&ma->normals[3 * triangle[1]], cp);
    par_shapes__copy3(next, pa);
    par_shapes__subtract3(next, pc);
    par_shapes__copy3(prev, pb);
    par_shapes__subtract3(prev, pc);
    par_shapes__cross3(cp, next, prev);
    par_shapes__add3(&ma->normals[3 * triangle[2]], cp);
    triangle += 3;
  }
  normal = ma->normals;
  for ( p = 0; p < ma->npoints; ++p )
  {
    par_shapes__normalize3(normal);
    normal += 3;
  }
}