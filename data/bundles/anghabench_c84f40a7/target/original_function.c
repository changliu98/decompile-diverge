int byte_row_gbk1 (int byte) {
  if (byte >= 0x81 && byte < 0xff)
    return byte-0x81;
  else
    return -1;
}