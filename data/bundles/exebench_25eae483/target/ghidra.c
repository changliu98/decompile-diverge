int intersect_triangle(double *orig,double *dir,double *vert0,double *vert1,double *vert2,double *t,
                      double *u,double *v)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double inv_det;
  double det;
  double qvec [3];
  double pvec [3];
  double tvec [3];
  double edge2 [3];
  double edge1 [3];
  double *t_local;
  double *vert2_local;
  double *vert1_local;
  double *vert0_local;
  double *dir_local;
  double *orig_local;
  int local_c;
  
  dVar1 = *vert1 - *vert0;
  dVar2 = vert1[1] - vert0[1];
  dVar3 = vert1[2] - vert0[2];
  dVar4 = *vert2 - *vert0;
  dVar5 = vert2[1] - vert0[1];
  dVar6 = vert2[2] - vert0[2];
  dVar7 = dir[1] * dVar6 + -(dir[2] * dVar5);
  dVar8 = dir[2] * dVar4 + -(*dir * dVar6);
  dVar9 = *dir * dVar5 + -(dir[1] * dVar4);
  dVar10 = dVar3 * dVar9 + dVar1 * dVar7 + dVar2 * dVar8;
  if ((dVar10 <= DAT_00103008) || (DAT_00103010 <= dVar10)) {
    dVar10 = DAT_00103018 / dVar10;
    dVar11 = *orig - *vert0;
    dVar12 = orig[1] - vert0[1];
    dVar13 = orig[2] - vert0[2];
    *u = (dVar13 * dVar9 + dVar11 * dVar7 + dVar12 * dVar8) * dVar10;
    if ((*u <= 0.0 && *u != 0.0) || (DAT_00103018 < *u)) {
      local_c = 0;
    }
    else {
      dVar7 = dVar12 * dVar3 + -(dVar13 * dVar2);
      dVar3 = dVar13 * dVar1 + -(dVar11 * dVar3);
      dVar1 = dVar11 * dVar2 + -(dVar12 * dVar1);
      *v = (dir[2] * dVar1 + *dir * dVar7 + dir[1] * dVar3) * dVar10;
      if ((*v <= 0.0 && *v != 0.0) || (DAT_00103018 < *u + *v)) {
        local_c = 0;
      }
      else {
        *t = (dVar6 * dVar1 + dVar4 * dVar7 + dVar5 * dVar3) * dVar10;
        local_c = 1;
      }
    }
  }
  else {
    local_c = 0;
  }
  return local_c;
}