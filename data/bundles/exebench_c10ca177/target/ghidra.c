void geom_matinv2d(double *m)

{
  double dVar1;
  double dVar2;
  double t;
  double d;
  double *m_local;
  
  dVar2 = DAT_00102008 / (*m * m[3] + -(m[1] * m[2]));
  dVar1 = *m;
  *m = dVar2 * m[3];
  m[1] = -dVar2 * m[1];
  m[2] = -dVar2 * m[2];
  m[3] = dVar2 * dVar1;
  return;
}