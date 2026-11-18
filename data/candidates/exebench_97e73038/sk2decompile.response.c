int intersect_triangle(double *orig, double *dir, double *v0, double *v1,
                       double *v2, double *t, double *u, double *v) {
  double edge1[3], edge2[3], tvec[3], v0t[3], pvec[3], qvec[3], det;
  edge1[0] = v1[0] - v0[0];
  edge1[1] = v1[1] - v0[1];
  edge1[2] = v1[2] - v0[2];
  edge2[0] = v2[0] - v0[0];
  edge2[1] = v2[1] - v0[1];
  edge2[2] = v2[2] - v0[2];
  tvec[0] = dir[1] * edge2[2] - dir[2] * edge2[1];
  tvec[1] = dir[2] * edge2[0] - dir[0] * edge2[2];
  tvec[2] = dir[0] * edge2[1] - dir[1] * edge2[0];
  det = edge1[0] * tvec[0] + edge1[1] * tvec[1] + edge1[2] * tvec[2];
  if (det < 0.000001) return 0;
  v0t[0] = orig[0] - v0[0];
  v0t[1] = orig[1] - v0[1];
  v0t[2] = orig[2] - v0[2];
  *u = tvec[0] * v0t[0] + tvec[1] * v0t[1] + tvec[2] * v0t[2];
  if (*u < 0.0 || *u > det) return 0;
  pvec[0] = v0t[1] * edge1[2] - v0t[2] * edge1[1];
  pvec[1] = v0t[2] * edge1[0] - v0t[0] * edge1[2];
  pvec[2] = v0t[0] * edge1[1] - v0t[1] * edge1[0];
  *v = dir[0] * pvec[0] + dir[1] * pvec[1] + dir[2] * pvec[2];
  if (*v < 0.0 || *u + *v > det) return 0;
  *t = edge2[0] * pvec[0] + edge2[1] * pvec[1] + edge2[2] * pvec[2];
  *t = 1.0 / det * *t;
  *u = 1.0 / det * *u;
  *v = 1.0 / det * *v;
  return 1;
}