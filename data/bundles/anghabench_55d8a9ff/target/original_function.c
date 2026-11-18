int byte_col_big5 (int byte) {
  if (byte >= 0x40 && byte < 0x7f)
    return byte-0x40;
  else if (byte >= 0xa1 && byte < 0xff)
    return byte-0x62;
  else
    return -1;
}