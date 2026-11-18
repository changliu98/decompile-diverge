int intersect_triangle(double *orig, double *dir, double *v0, double *v1,
                       double *v2, double *t, double *u, double *v) {
  double edge1[3], edge2[3], tvec[3], vec[3], qvec[3], pvec[3], det;
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
  if (det > -0.000001 && det < 0.000001) return 0;
  det = 1.0 / det;
  vec[0] = orig[0] - v0[0];
  vec[1] = orig[1] - v0[1];
  vec[2] = orig[2] - v0[2];
  *u = (vec[0] * tvec[0] + vec[1] * tvec[1] + vec[2] * tvec[2]) * det;
  if (*u < 0.0 || *u > 1.0) return 0;
  qvec[0] = vec[1] * edge1[2] - vec[2] * edge1[1];
  qvec[1] = vec[2] * edge1[0] - vec[0] * edge1[2];
  qvec[2] = vec[0] * edge1[1] - vec[1] * edge1[0];
  *v = (dir[0] * qvec[0] + dir[1] * qvec[1] + dir[2] * qvec[2]) * det;
  if (*v < 0.0 || *u + *v > 1.0) return 0;
  *t = (edge2[0] * qvec[0] + edge2[1] * qvec[1] + edge2[2] * qvec[2]) * det;
  return 1;
}