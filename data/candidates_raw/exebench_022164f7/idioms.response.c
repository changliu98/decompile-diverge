int line_plane_intersection(double *orig, double *dir, double *vert0, double *vert1, double *vert2, double *t, double *u, double *v)
{
  double edge1[3]; double edge2[3];
  double pvec[3]; double qvec[3];
  double tvec[3];
  double det;
  double tvec_dot_pvec;
  double tvec_dot_qvec;
  double tvec_dot_qvec_div_det;
  edge1[0] = vert1[0] - vert0[0];
  edge1[1] = vert1[1] - vert0[1];
  edge1[2] = vert1[2] - vert0[2];
  edge2[0] = vert2[0] - vert0[0];
  edge2[1] = vert2[1] - vert0[1];
  edge2[2] = vert2[2] - vert0[2];
  pvec[0] = dir[1] * edge2[2] - dir[2] * edge2[1];
  pvec[1] = dir[2] * edge2[0] - dir[0] * edge2[2];
  pvec[2] = dir[0] * edge2[1] - dir[1] * edge2[0];
  det = edge1[0] * pvec[0] + edge1[1] * pvec[1] + edge1[2] * pvec[2];
  if (det > 0.00001)
  {
    tvec[0] = orig[0] - vert0[0];
    tvec[1] = orig[1] - vert0[1];
    tvec[2] = orig[2] - vert0[2];
    tvec_dot_pvec = tvec[0] * pvec[0] + tvec[1] * pvec[1] + tvec[2] * pvec[2];
    if (tvec_dot_pvec < 0 || tvec_dot_pvec > det)
      return 0;
    qvec[0] = tvec[1] * edge1[2] - tvec[2] * edge1[1];
    qvec[1] = tvec[2] * edge1[0] - tvec[0] * edge1[2];
    qvec[2] = tvec[0] * edge1[1] - tvec[1] * edge1[0];
    tvec_dot_qvec = dir[0] * qvec[0] + dir[1] * qvec[1] + dir[2] * qvec[2];
    if (tvec_dot_qvec < 0 || tvec_dot_pvec + tvec_dot_qvec > det)
      return 0;
    tvec_dot_qvec_div_det = 1.0 / det;
    tvec_dot_pvec *= tvec_dot_qvec_div_det;
    tvec_dot_qvec *= tvec_dot_qvec_div_det;
    *t = tvec_dot_qvec + tvec_dot_pvec;
    *u = tvec_dot_pvec;
    *v = tvec_dot_qvec;
  }
  else if (det < -0.00001)
  {
    tvec[0] = orig[0] - vert0[0];
    tvec[1] = orig[1] - vert0[1];
    tvec[2] = orig[2] - vert0[2];
    *u = tvec[0] * pvec[0] + tvec[1] * pvec[1] + tvec[2] * pvec[2];
    if (*u < 0 || *u > det)
      return 0;
    qvec[0] = tvec[1] * edge1[2] - tvec[2] * edge1[1];
    qvec[1] = tvec[2] * edge1[0] - tvec[0] * edge1[2];
    qvec[2] = tvec[0] * edge1[1] - tvec[1] * edge1[0];
    *v = dir[0] * qvec[0] + dir[1] * qvec[1] + dir[2] * qvec[2];
    if (*v < 0 || *u + *v > det)
      return 0;
    tvec_dot_qvec_div_det = 1.0 / det;
    tvec_dot_pvec = *u * tvec_dot_qvec_div_det;
    tvec_dot_qvec = *v * tvec_dot_qvec_div_det;
    *t = tvec_dot_qvec + tvec_dot_pvec;
    *u = tvec_dot_pvec;
    *v = tvec_dot_qvec;
  }
  else
    return 0;
  return 1;
}