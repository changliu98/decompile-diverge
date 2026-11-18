void sjis2jis(unsigned char *sjis_x, unsigned char *sjis_y) {
  unsigned char sjis_x_base, sjis_y_base;
  sjis_x_base = (*sjis_x < 0xa0) ? 0x70 : 0xb0;
  sjis_y_base = (*sjis_y < 0x9f) ? 0x1f : 0x7e;
  *sjis_x = (*sjis_x - sjis_x_base) * 2 - (*sjis_y < 0x9f);
  *sjis_y -= sjis_y_base;
}