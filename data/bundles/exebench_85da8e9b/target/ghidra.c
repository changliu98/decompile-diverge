void unpack_dxt(uchar mask,unsigned_short col1,unsigned_short col2,uchar *target)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  unsigned_short b2;
  unsigned_short g2;
  unsigned_short r2;
  unsigned_short b1;
  unsigned_short g1;
  unsigned_short r1;
  uchar *target_local;
  unsigned_short col2_local;
  unsigned_short col1_local;
  uchar mask_local;
  
  uVar1 = (col1 & 0x1f) << 3;
  uVar2 = col1 >> 3 & 0xfc;
  uVar3 = col1 >> 8 & 0xf8;
  uVar4 = (col2 & 0x1f) << 3;
  uVar5 = col2 >> 3 & 0xfc;
  uVar6 = col2 >> 8 & 0xf8;
  switch(mask) {
  case '\0':
    *target = (uchar)uVar1;
    target[1] = (uchar)uVar2;
    target[2] = (uchar)uVar3;
    break;
  case '\x01':
    *target = (uchar)uVar4;
    target[1] = (uchar)uVar5;
    target[2] = (uchar)uVar6;
    break;
  case '\x02':
    if (col2 < col1) {
      *target = (uchar)((ulong)(long)(int)((uint)uVar1 * 2 + (uint)uVar4) / 3);
      target[1] = (uchar)((ulong)(long)(int)((uint)uVar2 * 2 + (uint)uVar5) / 3);
      target[2] = (uchar)((ulong)(long)(int)((uint)uVar3 * 2 + (uint)uVar6) / 3);
    }
    else {
      *target = (uchar)((ulong)((uint)uVar1 + (uint)uVar4) / 2);
      target[1] = (uchar)((ulong)((uint)uVar2 + (uint)uVar5) / 2);
      target[2] = (uchar)((ulong)((uint)uVar3 + (uint)uVar6) / 2);
    }
    break;
  case '\x03':
    if (col2 < col1) {
      *target = (uchar)((ulong)(long)(int)((uint)uVar1 + (uint)uVar4 * 2) / 3);
      target[1] = (uchar)((ulong)(long)(int)((uint)uVar2 + (uint)uVar5 * 2) / 3);
      target[2] = (uchar)((ulong)(long)(int)((uint)uVar3 + (uint)uVar6 * 2) / 3);
    }
    else {
      target[2] = '\0';
      target[1] = '\0';
      *target = '\0';
    }
  }
  return;
}