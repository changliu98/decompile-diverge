/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(int v,int t)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double windchill;
  int t_local;
  int v_local;
  
  dVar1 = (double)t * DAT_00102020 + _DAT_00102028;
  dVar2 = pow((double)v,DAT_00102008);
  dVar2 = dVar2 * DAT_00102018;
  dVar3 = DAT_00102010 * (double)t;
  dVar4 = pow((double)v,DAT_00102008);
  dVar1 = round(dVar3 * dVar4 + dVar2 + dVar1);
  return (int)dVar1;
}