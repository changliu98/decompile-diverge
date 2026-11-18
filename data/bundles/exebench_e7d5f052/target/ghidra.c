void SJIStoJIS(int *p1,int *p2)

{
  uint uVar1;
  int iVar2;
  undefined4 local_2c;
  int cellOffset;
  int rowOffset;
  int adjust;
  uchar c2;
  uchar c1;
  int *p2_local;
  int *p1_local;
  
  uVar1 = (uint)((byte)*p2 < 0x9f);
  iVar2 = 0xb0;
  if ((byte)*p1 < 0xa0) {
    iVar2 = 0x70;
  }
  if (uVar1 == 0) {
    local_2c = 0x7e;
  }
  else {
    local_2c = (0x7f < (byte)*p2) + 0x1f;
  }
  *p1 = ((*p1 & 0xffU) - iVar2) * 2 - uVar1;
  *p2 = *p2 - local_2c;
  return;
}