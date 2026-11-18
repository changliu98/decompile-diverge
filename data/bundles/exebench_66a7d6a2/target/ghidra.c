void swapdouble(double *dbl)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int *dd;
  int t;
  double *dbl_local;
  
  iVar1 = *(int *)dbl;
  uVar2 = *(uint *)dbl;
  uVar3 = *(uint *)dbl;
  uVar4 = *(uint *)dbl;
  *(uint *)dbl = *(int *)((long)dbl + 4) << 0x18 | (*(uint *)((long)dbl + 4) & 0xff00) << 8 |
                 (*(uint *)((long)dbl + 4) & 0xff0000) >> 8 | *(uint *)((long)dbl + 4) >> 0x18;
  *(uint *)((long)dbl + 4) =
       iVar1 << 0x18 | (uVar2 & 0xff00) << 8 | (uVar3 & 0xff0000) >> 8 | uVar4 >> 0x18;
  return;
}