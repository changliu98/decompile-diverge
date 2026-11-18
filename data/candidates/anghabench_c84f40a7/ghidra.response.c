int byte_row_gbk1(int byte)

{
  int byte_local;
  undefined4 local_c;
  
  if ((byte < 0x81) || (0xfe < byte)) {
    local_c = -1;
  }
  else {
    local_c = byte + -0x81;
  }
  return local_c;
}