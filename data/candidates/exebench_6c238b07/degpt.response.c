int genx(uchar *dst,uchar *field)

{
  bool bVar1;
  int iVar2;
  int x;
  uint e;
  int i;
  short index [256];
  int error;
  uchar *field_local;
  uchar *dst_local;
  
  bVar1 = false;
  for (i = 0; i < 0x100; i = i + 1) {
    index[i] = -1;
  }
  for (i = 0; i < 0x100; i = i + 1) {
    if (index[(uint)field[i]] == -1) {
      index[(uint)field[i]] = (short)i;
    }
    else {
      bVar1 = true;
    }
  }
  for (i = 0; i < 0x100; i = i + 1) {
    dst[i] = (uchar)index[i];
  }
  iVar2 = -1;
  if (!bVar1) {
    iVar2 = 0;
  }
  return iVar2;
}