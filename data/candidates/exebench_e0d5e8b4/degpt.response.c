void dstsub4(int n,float *a)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float xr;
  float wdi;
  float wdr;
  float wki;
  int m;
  float *a_local;
  int n_local;
  
  fVar2 = DAT_00102004;
  iVar3 = n >> 1;
  if (iVar3 == 2) {
    fVar4 = DAT_0010200c * DAT_00102004;
    fVar5 = DAT_00102008 * DAT_00102004;
    fVar1 = a[3];
    a[3] = fVar4 * a[3] + fVar5 * a[1];
    a[1] = fVar5 * fVar1 + -(fVar4 * a[1]);
  }
  a[iVar3] = fVar2 * a[iVar3];
  return;
}