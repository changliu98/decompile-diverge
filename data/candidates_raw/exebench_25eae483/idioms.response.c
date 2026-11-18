int ray_triangle(double *ray_orig, double *ray_dir, double *v0, double *v1, double *v2, double *ray_t, double *ray_u, double *ray_v)
{
  double e1[3]; double e2[3]; double pvec[3]; double tvec[3]; double qvec[3];
  double det; double inv_det;
  double u; double v;
  double t;
  e1[0] = v1[0] - v0[0];
  e1[1] = v1[1] - v0[1];
  e1[2] = v1[2] - v0[2];
  e2[0] = v2[0] - v0[0];
  e2[1] = v2[1] - v0[1];
  e2[2] = v2[2] - v0[2];
  pvec[0] = ray_dir[1] * e2[2] - ray_dir[2] * e2[1];
  pvec[1] = ray_dir[2] * e2[0] - ray_dir[0] * e2[2];
  pvec[2] = ray_dir[0] * e2[1] - ray_dir[1] * e2[0];
  det = pvec[0] * e1[0] + pvec[1] * e1[1] + pvec[2] * e1[2];
  if (det < -0.000001 || det > 0.000001)
    inv_det = 1.0 / det;
  else
    return 0;
  tvec[0] = ray_orig[0] - v0[0];
  tvec[1] = ray_orig[1] - v0[1];
  tvec[2] = ray_orig[2] - v0[2];
  u = (tvec[0] * pvec[0] + tvec[1] * pvec[1] + tvec[2] * pvec[2]) * inv_det;
  if (u < 0.0 || u > 1.0)
    return 0;
  qvec[0] = tvec[1] * e1[2] - tvec[2] * e1[1];
  qvec[1] = tvec[2] * e1[0] - tvec[0] * e1[2];
  qvec[2] = tvec[0] * e1[1] - tvec[1] * e1[0];
  v = (ray_dir[0] * qvec[0] + ray_dir[1] * qvec[1] + ray_dir[2] * qvec[2]) * inv_det;
  if (v < 0.0 || u + v > 1.0)
    return 0;
  t = (e2[0] * qvec[0] + e2[1] * qvec[1] + e2[2] * qvec[2]) * inv_det;
  *ray_t = t;
  *ray_u = u;
  *ray_v = v;
  return 1;
}