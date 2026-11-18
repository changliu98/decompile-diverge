int intersect_triangle(VECTOR rO, VECTOR rD, VECTOR v0, VECTOR v1, VECTOR v2, double *t, double *u, double *v)
{
 VECTOR edge1, edge2, tvec, pvec, qvec;
 double det,inv_det;

 { edge1.x = v1->x - v0->x; edge1.y = v1->y - v0->y; edge1.z = v1->z - v0->z; };
 { edge2.x = v2->x - v0->x; edge2.y = v2->y - v0->y; edge2.z = v2->z - v0->z; };

 { pvec.x = rD->y * edge2.z + fabs__bench(rD->z * edge2.y); pvec.y = rD->z * edge2.x + fabs__bench(rD->x * edge2.z); pvec.z = rD->x * edge2.y + fabs__bench(rD->y * edge2.x); };

 det = (edge1.x * pvec.x + edge1.y * pvec.y + edge1.z * pvec.z);

 if (det < 0.000001)
  return 0;

 { tvec.x = rO->x - v0->x; tvec.y = rO->y - v0->y; tvec.z = rO->z - v0->z; };

 *u = (tvec.x * pvec.x + tvec.y * pvec.y + tvec.z * pvec.z);
 if (*u < 0.0 || *u > det)
  return 0;

 { qvec.x = tvec.y * edge1.z + fabs__bench(tvec.z * edge1.y); qvec.y = tvec.z * edge1.x + fabs__bench(tvec.x * edge1.z); qvec.z = tvec.x * edge1.y + fabs__bench(tvec.y * edge1.x); };

 *v = (rD->x * qvec.x + rD->y * qvec.y + rD->z * qvec.z);
 if (*v < 0.0 || *u + *v > det)
  return 0;

 inv_det = 1.0 / det;

 *t = (edge2.x * qvec.x + edge2.y * qvec.y + edge2.z * qvec.z) * inv_det;
 (*u) *= inv_det;
 (*v) *= inv_det;

 return 1;
}