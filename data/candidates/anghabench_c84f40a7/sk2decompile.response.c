int byte_row_gbk1(int c) {
  if (c >= 0x81 && c < 0xff)
    return c - 0x81;
  else
    return -1;
}