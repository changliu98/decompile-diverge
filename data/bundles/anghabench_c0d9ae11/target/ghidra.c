int check_crc_flex(uchar *cp,int size)

{
  unsigned_short crc;
  int size_local;
  uchar *cp_local;
  int local_c;
  
  crc = 0xffff;
  size_local = size;
  cp_local = cp;
  if (size < 3) {
    local_c = -1;
  }
  else {
    while (size_local != 0) {
      crc = crc << 8 ^ crc_flex_table[(int)((int)(uint)crc >> 8 ^ (uint)*cp_local)];
      size_local = size_local + -1;
      cp_local = cp_local + 1;
    }
    if (crc == 0x7070) {
      local_c = 0;
    }
    else {
      local_c = -1;
    }
  }
  return local_c;
}