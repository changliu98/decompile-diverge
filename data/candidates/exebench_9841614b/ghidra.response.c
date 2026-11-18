int UnpackImmediate(uint val,int *outByte,int *outShift)

{
  int i;
  int *outShift_local;
  int *outByte_local;
  uint val_local;
  int local_c;
  
  if (val == 0) {
    *outByte = 0;
    *outShift = 0;
    local_c = 1;
  }
  else {
    val_local = val;
    for (i = 0; i < 0xf; i = i + 1) {
      if (((val_local & 3) != 0) && (val_local < 0x100)) {
        *outByte = val_local;
        *outShift = i;
        return 1;
      }
      if ((val_local & 3) != 0) {
        return 0;
      }
      val_local = val_local >> 2;
    }
    local_c = 0;
  }
  return local_c;
}