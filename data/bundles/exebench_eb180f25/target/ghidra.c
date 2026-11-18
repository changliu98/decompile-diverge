double Mat_doubleSwap(double *a)

{
  double dVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  anon_union_8_2_94730002 tmp;
  double *a_local;
  
  dVar1 = *a;
  tmp.a[7] = (char)((ulong)dVar1 >> 0x38);
  uVar3 = tmp.a[7];
  tmp.a[0] = SUB81(dVar1,0);
  tmp.a[6] = (char)((ulong)dVar1 >> 0x30);
  uVar2 = tmp.a[6];
  tmp.a[1] = (char)((ulong)dVar1 >> 8);
  tmp.a[7] = tmp.a[0];
  tmp.a[6] = tmp.a[1];
  tmp.a[1] = uVar2;
  tmp.a[0] = uVar3;
  tmp.a[5] = (char)((ulong)dVar1 >> 0x28);
  uVar2 = tmp.a[5];
  tmp.a[2] = (char)((ulong)dVar1 >> 0x10);
  tmp.a[5] = tmp.a[2];
  tmp.a[2] = uVar2;
  tmp.a[4] = (char)((ulong)dVar1 >> 0x20);
  uVar2 = tmp.a[4];
  tmp.a[3] = (char)((ulong)dVar1 >> 0x18);
  tmp.a[4] = tmp.a[3];
  tmp.a[3] = uVar2;
  *a = (double)tmp;
  return *a;
}