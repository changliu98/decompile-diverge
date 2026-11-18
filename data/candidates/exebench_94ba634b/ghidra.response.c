void _jis_shift(int *p1,int *p2)

{
  uint uVar1;
  int iVar2;
  undefined4 local_28;
  int cellOffset;
  int rowOffset;
  uchar c2;
  uchar c1;
  int *p2_local;
  int *p1_local;
  
  uVar1 = *p1;
  iVar2 = 0xb0;
  if ((byte)uVar1 < 0x5f) {
    iVar2 = 0x70;
  }
  if ((uVar1 & 0xff) % 2 == 0) {
    local_28 = 0x7e;
  }
  else {
    local_28 = 0x1f;
    if (0x5f < (byte)*p2) {
      local_28 = 0x20;
    }
  }
  *p1 = ((int)((uVar1 & 0xff) + 1) >> 1) + iVar2;
  *p2 = local_28 + *p2;
  return;
}