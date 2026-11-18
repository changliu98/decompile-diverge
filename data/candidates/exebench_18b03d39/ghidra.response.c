void si_swapl(int *d)

{
  int iVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  uchar tmp;
  anon_union_4_2_94730047 u;
  int *d_local;
  
  iVar1 = *d;
  u.c[0] = (uchar)iVar1;
  uVar2 = u.c[0];
  u.c[3] = (uchar)((uint)iVar1 >> 0x18);
  u.c[1] = (uchar)((uint)iVar1 >> 8);
  uVar3 = u.c[1];
  u.c[2] = (uchar)((uint)iVar1 >> 0x10);
  u.c[1] = u.c[2];
  u.c[0] = u.c[3];
  u.c[2] = uVar3;
  u.c[3] = uVar2;
  *d = (int)u;
  return;
}