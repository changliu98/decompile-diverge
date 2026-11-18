void lin_solve_3(double *x,double *A,double *y)

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
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double inv8;
  double inv7;
  double inv6;
  double inv5;
  double inv4;
  double inv3;
  double inv2;
  double inv1;
  double inv0;
  double idet;
  double c;
  double b;
  double a;
  double *y_local;
  double *A_local;
  double *x_local;
  
  dVar17 = A[4] * A[8] + -(A[5] * A[7]);
  dVar18 = A[5] * A[6] + -(A[3] * A[8]);
  dVar19 = A[3] * A[7] + -(A[4] * A[6]);
  dVar20 = DAT_00102010 / (A[2] * dVar19 + *A * dVar17 + A[1] * dVar18);
  dVar1 = *A;
  dVar2 = A[8];
  dVar3 = A[2];
  dVar4 = A[6];
  dVar5 = A[2];
  dVar6 = A[3];
  dVar7 = *A;
  dVar8 = A[5];
  dVar9 = A[1];
  dVar10 = A[6];
  dVar11 = *A;
  dVar12 = A[7];
  dVar13 = *A;
  dVar14 = A[4];
  dVar15 = A[1];
  dVar16 = A[3];
  *x = dVar20 * ((A[1] * A[5] + -(A[2] * A[4])) * y[2] +
                dVar17 * *y + (A[2] * A[7] + -(A[1] * A[8])) * y[1]);
  x[1] = dVar20 * ((dVar5 * dVar6 + -(dVar7 * dVar8)) * y[2] +
                  dVar18 * *y + (dVar1 * dVar2 + -(dVar3 * dVar4)) * y[1]);
  x[2] = dVar20 * ((dVar13 * dVar14 + -(dVar15 * dVar16)) * y[2] +
                  dVar19 * *y + (dVar9 * dVar10 + -(dVar11 * dVar12)) * y[1]);
  return;
}