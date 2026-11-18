int jpeg_size(unsigned char *buf, unsigned int len, unsigned int *width,
              unsigned int *height) {
  unsigned int pos, next;
  unsigned short seg_len;
  if (len < 4) return -1;
  if (buf[0] != 0xff || buf[1] != 0xd8 || buf[2] != 0xff || buf[3] != 0xe0)
    return -1;
  pos = 4;
  if (len < 11) return -1;
  if (buf[6] != 'J' || buf[7] != 'F' || buf[8] != 'I' || buf[9] != 'F' ||
      buf[10] != 0)
    return -1;
  seg_len = buf[4] * 256 + buf[5];
  while (pos < len) {
    next = pos + seg_len;
    if (next + 1 >= len) return -1;
    if (buf[next] != 0xff) return -1;
    if (buf[next + 1] == 0xc0) {
      *height = buf[next + 5] * 256 + buf[next + 6];
      *width = buf[next + 7] * 256 + buf[next + 8];
      return 0;
    }
    pos = next + 2;
    seg_len = buf[pos] * 256 + buf[pos + 1];
  }
  return -1;
}