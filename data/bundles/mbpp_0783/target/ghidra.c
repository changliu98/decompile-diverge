void func0(int r,int g,int b,double *h,double *s,double *v)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double df;
  double mn;
  double mx;
  double bd;
  double gd;
  double rd;
  double *v_local;
  double *s_local;
  double *h_local;
  int b_local;
  int g_local;
  int r_local;
  
  dVar1 = (double)r / DAT_00102008;
  dVar2 = (double)g / DAT_00102008;
  dVar3 = (double)b / DAT_00102008;
  dVar5 = dVar3;
  if (dVar3 <= dVar2) {
    dVar5 = dVar2;
  }
  dVar4 = (double)(~-(ulong)NAN(dVar2) & (ulong)dVar5 | -(ulong)NAN(dVar2) & (ulong)dVar3);
  dVar5 = dVar4;
  if (dVar4 <= dVar1) {
    dVar5 = dVar1;
  }
  dVar4 = (double)(~-(ulong)NAN(dVar1) & (ulong)dVar5 | -(ulong)NAN(dVar1) & (ulong)dVar4);
  dVar5 = dVar3;
  if (dVar2 <= dVar3) {
    dVar5 = dVar2;
  }
  dVar6 = (double)(~-(ulong)NAN(dVar2) & (ulong)dVar5 | -(ulong)NAN(dVar2) & (ulong)dVar3);
  dVar5 = dVar6;
  if (dVar1 <= dVar6) {
    dVar5 = dVar1;
  }
  dVar5 = dVar4 - (double)(~-(ulong)NAN(dVar1) & (ulong)dVar5 | -(ulong)NAN(dVar1) & (ulong)dVar6);
  *h = 0.0;
  if (0.0 < dVar5) {
    if ((dVar4 != dVar1) || (NAN(dVar4) || NAN(dVar1))) {
      if ((dVar4 != dVar2) || (NAN(dVar4) || NAN(dVar2))) {
        if ((dVar4 == dVar3) && (!NAN(dVar4) && !NAN(dVar3))) {
          dVar1 = fmod(((dVar1 - dVar2) / dVar5) * DAT_00102018 + DAT_00102020,DAT_00102010);
          *h = dVar1;
        }
      }
      else {
        dVar1 = fmod(((dVar3 - dVar1) / dVar5) * DAT_00102018 + DAT_00102028,DAT_00102010);
        *h = dVar1;
      }
    }
    else {
      dVar1 = fmod(((dVar2 - dVar3) / dVar5) * DAT_00102018 + DAT_00102010,DAT_00102010);
      *h = dVar1;
    }
  }
  if ((dVar4 != 0.0) || (NAN(dVar4))) {
    *s = (dVar5 / dVar4) * DAT_00102030;
  }
  else {
    *s = 0.0;
  }
  *v = DAT_00102030 * dVar4;
  return;
}