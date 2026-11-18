int readUTF8(unsigned char *buf, int len, int pos, int *size) {
  int c = 0;
  if (pos < len - 1 && (buf[pos] & 0xE0) == 0xC0 &&
      (buf[pos + 1] & 0xC0) == 0x80) {
    *size = 2;
    c = ((buf[pos] & 0x1F) << 6) + (buf[pos + 1] & 0x3F);
    if (c < 0x80) c = 0;
  } else if (pos < len - 2 && (buf[pos] & 0xF0) == 0xE0 &&
             (buf[pos + 1] & 0xC0) == 0x80 && (buf[pos + 2] & 0xC0) == 0x80) {
    *size = 3;
    c = (((buf[pos] & 0x0F) << 6) + (buf[pos + 1] & 0x3F)) << 6;
    c += (buf[pos + 2] & 0x3F);
    if (c < 0x800) c = 0;
  } else if (pos < len - 3 && (buf[pos] & 0xF8) == 0xF0 &&
             (buf[pos + 1] & 0xC0) == 0x80 && (buf[pos + 2] & 0xC0) == 0x80 &&
             (buf[pos + 3] & 0xC0) == 0x80) {
    *size = 4;
    c = ((((buf[pos] & 0x07) << 6) + (buf[pos + 1] & 0x3F)) << 6) << 6;
    c += (buf[pos + 2] & 0x3F);
    c += (buf[pos + 3] & 0x3F);
    if (c < 0x10000) c = 0;
  }
  return c;
}