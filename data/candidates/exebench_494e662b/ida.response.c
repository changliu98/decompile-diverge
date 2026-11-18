void __cdecl denormF(double *F, double *A1, double *A2)
{
  double y; // [rsp+0h] [rbp-30h]
  double ya; // [rsp+0h] [rbp-30h]
  double x; // [rsp+8h] [rbp-28h]
  double xa; // [rsp+8h] [rbp-28h]
  double r; // [rsp+10h] [rbp-20h]
  double ra; // [rsp+10h] [rbp-20h]

  r = *A2;
  x = A2[1];
  y = A2[2];
  F[6] = x * *F + y * F[3] + F[6];
  F[7] = x * F[1] + y * F[4] + F[7];
  F[8] = x * F[2] + y * F[5] + F[8];
  *F = r * *F;
  F[1] = r * F[1];
  F[2] = r * F[2];
  F[3] = r * F[3];
  F[4] = r * F[4];
  F[5] = r * F[5];
  ra = *A1;
  xa = A1[1];
  ya = A1[2];
  F[2] = xa * *F + ya * F[1] + F[2];
  F[5] = xa * F[3] + ya * F[4] + F[5];
  F[8] = xa * F[6] + ya * F[7] + F[8];
  *F = ra * *F;
  F[3] = ra * F[3];
  F[6] = ra * F[6];
  F[1] = ra * F[1];
  F[4] = ra * F[4];
  F[7] = ra * F[7];
}