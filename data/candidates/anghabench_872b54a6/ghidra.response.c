int byte_row_johab_hangul(int byte)

{
  int byte_local;
  undefined4 local_c;
  
  if ((byte < 0x84) || (0xd3 < byte)) {
    local_c = -1;
  }
  else {
    local_c = byte + -0x84;
  }
  return local_c;
}