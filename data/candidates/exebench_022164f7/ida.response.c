int __cdecl intersect_triangle1(
        double *orig,
        double *dir,
        double *vert0,
        double *vert1,
        double *vert2,
        double *t,
        double *u,
        double *v)
{
  double det; // [rsp+8h] [rbp-D8h]
  double qvec; // [rsp+10h] [rbp-D0h]
  double qvec_8; // [rsp+18h] [rbp-C8h]
  double qvec_16; // [rsp+20h] [rbp-C0h]
  double pvec; // [rsp+30h] [rbp-B0h]
  double pvec_8; // [rsp+38h] [rbp-A8h]
  double pvec_16; // [rsp+40h] [rbp-A0h]
  double tvec; // [rsp+50h] [rbp-90h]
  double tveca; // [rsp+50h] [rbp-90h]
  double tvec_8; // [rsp+58h] [rbp-88h]
  double tvec_8a; // [rsp+58h] [rbp-88h]
  double tvec_16; // [rsp+60h] [rbp-80h]
  double tvec_16a; // [rsp+60h] [rbp-80h]
  double edge2; // [rsp+70h] [rbp-70h]
  double edge2_8; // [rsp+78h] [rbp-68h]
  double edge2_16; // [rsp+80h] [rbp-60h]
  double edge1; // [rsp+90h] [rbp-50h]
  double edge1_8; // [rsp+98h] [rbp-48h]
  double edge1_16; // [rsp+A0h] [rbp-40h]

  edge1 = *vert1 - *vert0;
  edge1_8 = vert1[1] - vert0[1];
  edge1_16 = vert1[2] - vert0[2];
  edge2 = *vert2 - *vert0;
  edge2_8 = vert2[1] - vert0[1];
  edge2_16 = vert2[2] - vert0[2];
  pvec = dir[1] * edge2_16 - dir[2] * edge2_8;
  pvec_8 = dir[2] * edge2 - *dir * edge2_16;
  pvec_16 = *dir * edge2_8 - dir[1] * edge2;
  det = edge1_16 * pvec_16 + edge1 * pvec + edge1_8 * pvec_8;
  if ( det <= 0.00001 )
  {
    if ( det >= -0.00001 )
      return 0;
    tveca = *orig - *vert0;
    tvec_8a = orig[1] - vert0[1];
    tvec_16a = orig[2] - vert0[2];
    *u = tvec_16a * pvec_16 + tveca * pvec + tvec_8a * pvec_8;
    if ( *u > 0.0 || det > *u )
      return 0;
    qvec = tvec_8a * edge1_16 - tvec_16a * edge1_8;
    qvec_8 = tvec_16a * edge1 - tveca * edge1_16;
    qvec_16 = tveca * edge1_8 - tvec_8a * edge1;
    *v = dir[2] * qvec_16 + *dir * qvec + dir[1] * qvec_8;
    if ( *v > 0.0 || det > *u + *v )
      return 0;
    goto LABEL_18;
  }
  tvec = *orig - *vert0;
  tvec_8 = orig[1] - vert0[1];
  tvec_16 = orig[2] - vert0[2];
  *u = tvec_16 * pvec_16 + tvec * pvec + tvec_8 * pvec_8;
  if ( *u >= 0.0 && *u <= det )
  {
    qvec = tvec_8 * edge1_16 - tvec_16 * edge1_8;
    qvec_8 = tvec_16 * edge1 - tvec * edge1_16;
    qvec_16 = tvec * edge1_8 - tvec_8 * edge1;
    *v = dir[2] * qvec_16 + *dir * qvec + dir[1] * qvec_8;
    if ( *v < 0.0 || *u + *v > det )
      return 0;
LABEL_18:
    *t = (edge2_16 * qvec_16 + edge2 * qvec + edge2_8 * qvec_8) * (1.0 / det);
    *u = 1.0 / det * *u;
    *v = 1.0 / det * *v;
    return 1;
  }
  return 0;
}