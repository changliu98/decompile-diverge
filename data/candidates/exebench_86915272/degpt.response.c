void rahms(double ra,int *h,int *m,float *s)

{
  int iVar1;
  double dVar2;
  int itemp;
  double temp;
  float *s_local;
  int *m_local;
  int *h_local;
  double ra_local;
  
  temp = ra;
  if (ra < 0.0) {
    temp = DAT_00102008 + ra;
  }
  if (DAT_00102008 < temp) {
    temp = temp - DAT_00102008;
  }
  dVar2 = temp / DAT_00102018;
  iVar1 = (int)dVar2;
  *h = iVar1;
  dVar2 = DAT_00102010 * (dVar2 - (double)iVar1);
  iVar1 = (int)dVar2;
  *m = iVar1;
  *s = (float)(DAT_00102010 * (dVar2 - (double)iVar1));
  return;
}