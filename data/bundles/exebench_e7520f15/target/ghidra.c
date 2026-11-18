int CalcOffsetAndShift(int x,int y,size_t *offset,size_t *shift)

{
  size_t *shift_local;
  size_t *offset_local;
  int y_local;
  int x_local;
  undefined4 local_c;
  
  if ((((x < 0) || (0x53 < x)) || (y < 0)) || (0x2f < y)) {
    local_c = -1;
  }
  else if ((offset == (size_t *)0x0) || (shift == (size_t *)0x0)) {
    local_c = -1;
  }
  else {
    *offset = (long)(x + (y / 8) * 0x54);
    *shift = (long)(y % 8);
    local_c = 0;
  }
  return local_c;
}