int subprocess_error_from_errno(int error)

{
  int error_local;
  int local_c;
  
  if (error == 1) {
LAB_0010007f:
    local_c = -5;
  }
  else {
    if (error == 2) {
      return -4;
    }
    if (error != 0xc) {
      if (error == 0xd) goto LAB_0010007f;
      if (error == 0x14) {
        return -4;
      }
      if (1 < error - 0x17U) {
        return -1;
      }
    }
    local_c = -6;
  }
  return local_c;
}