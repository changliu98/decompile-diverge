void decdms(double dec,int *d,int *m,float *s)

{
  int iVar1;
  double dVar2;
  int itemp;
  double temp;
  float *s_local;
  int *m_local;
  int *d_local;
  double dec_local;
  
  *d = (int)dec;
  temp = dec - (double)(int)dec;
  if (temp < 0.0) {
    temp = -temp;
  }
  dVar2 = DAT_00102008 * temp;
  iVar1 = (int)dVar2;
  *m = iVar1;
  *s = (float)(DAT_00102008 * (dVar2 - (double)iVar1));
  return;
}