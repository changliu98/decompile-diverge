int unicoder_utf16_decode(uint *result,uchar *p,uint endianness)

{
  ushort uVar1;
  ushort uVar2;
  uint lowSurrogate;
  uint highSurrogate;
  uint dbyteB;
  uint dbyteA;
  uint endianness_local;
  uchar *p_local;
  uint *result_local;
  int local_c;
  
  if ((endianness == 2) || (endianness == 1)) {
    if (p == (uchar *)0x0) {
      local_c = -1;
    }
    else if (result == (uint *)0x0) {
      local_c = -1;
    }
    else {
      if (endianness == 1) {
        uVar1 = *(ushort *)p;
        uVar2 = *(ushort *)(p + 2);
      }
      else {
        uVar1 = CONCAT11(*p,p[1]);
        uVar2 = CONCAT11(p[2],p[3]);
      }
      dbyteA = (uint)uVar1;
      dbyteB = (uint)uVar2;
      if ((dbyteA < 0xd800) || (0xdfff < dbyteA)) {
        if (dbyteA < 0x110000) {
          *result = dbyteA;
          local_c = 2;
        }
        else {
          local_c = -0x10;
        }
      }
      else if ((dbyteA < 0xd800) || (0xdbff < dbyteA)) {
        local_c = -8;
      }
      else if ((dbyteB < 0xdc00) || (0xdfff < dbyteB)) {
        local_c = -8;
      }
      else {
        *result = 0;
        *result = dbyteA & 0x3ff | *result;
        *result = *result << 10;
        *result = dbyteB & 0x3ff | *result;
        *result = *result + 0x10000;
        local_c = 4;
      }
    }
  }
  else {
    local_c = -4;
  }
  return local_c;
}