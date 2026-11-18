int rdbEncodeInteger(longlong value,uchar *enc)

{
  uchar uVar1;
  uchar uVar2;
  uchar *enc_local;
  longlong value_local;
  int local_c;
  
  uVar1 = (uchar)value;
  if ((value < -0x80) || (0x7f < value)) {
    uVar2 = (uchar)((ulong)value >> 8);
    if ((value < -0x8000) || (0x7fff < value)) {
      if ((value < -0x80000000) || (0x7fffffff < value)) {
        local_c = 0;
      }
      else {
        *enc = (byte)(RDB_ENCVAL << 6) | (byte)RDB_ENC_INT32;
        enc[1] = uVar1;
        enc[2] = uVar2;
        enc[3] = (uchar)((ulong)value >> 0x10);
        enc[4] = (uchar)((ulong)value >> 0x18);
        local_c = 5;
      }
    }
    else {
      *enc = (byte)(RDB_ENCVAL << 6) | (byte)RDB_ENC_INT16;
      enc[1] = uVar1;
      enc[2] = uVar2;
      local_c = 3;
    }
  }
  else {
    *enc = (byte)(RDB_ENCVAL << 6) | (byte)RDB_ENC_INT8;
    enc[1] = uVar1;
    local_c = 2;
  }
  return local_c;
}