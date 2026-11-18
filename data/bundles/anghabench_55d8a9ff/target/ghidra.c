int byte_col_big5(int byte)

{
  int byte_local;
  undefined4 local_c;
  
  if ((byte < 0x40) || (0x7e < byte)) {
    if ((byte < 0xa1) || (0xfe < byte)) {
      local_c = -1;
    }
    else {
      local_c = byte + -0x62;
    }
  }
  else {
    local_c = byte + -0x40;
  }
  return local_c;
}