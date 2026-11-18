int ray_triangle(double *rayorig, double *raydir, double *vert0, double *vert1, double *vert2, double *t, double *u, double *v)
{
  double edge1[3]; double edge2[3]; double pvec[3]; double tvec[3]; double qvec[3];
  double det;
  edge1[0] = vert1[0] - vert0[0];
  edge1[1] = vert1[1] - vert0[1];
  edge1[2] = vert1[2] - vert0[2];
  edge2[0] = vert2[0] - vert0[0];
  edge2[1] = vert2[1] - vert0[1];
  edge2[2] = vert2[2] - vert0[2];
  pvec[0] = raydir[1] * edge2[2] - raydir[2] * edge2[1];
  pvec[1] = raydir[2] * edge2[0] - raydir[0] * edge2[2];
  pvec[2] = raydir[0] * edge2[1] - raydir[1] * edge2[0];
  det = edge1[0] * pvec[2] + edge1[1] * pvec[1] + edge1[2] * pvec[0];
  if (det < 0.000001)
    return (0);
  tvec[0] = rayorig[0] - vert0[0];
  tvec[1] = rayorig[1] - vert0[1];
  tvec[2] = rayorig[2] - vert0[2];
  *u = tvec[0] * pvec[2] + tvec[1] * pvec[1] + tvec[2] * pvec[0];
  if ( *u < 0.0 || *u > det )
    return (0);
  qvec[1] = tvec[0] * edge1[2] - tvec[2] * edge1[0];
  qvec[2] = tvec[2] * edge1[1] - tvec[1] * edge1[2];
  qvec[0] = tvec[1] * edge1[0] - tvec[0] * edge1[1];
  *v = raydir[2] * qvec[2] + raydir[0] * qvec[0] + raydir[1] * qvec[1];
  if ( *v < 0.0 || *u + *v > det )
    return (0);
  *t = edge2[0] * qvec[2] + edge2[1] * qvec[1] + edge2[2] * qvec[0];
  *t = *t / det;
  *u = *u / det;
  *v = *v / det;
  return (1);
}