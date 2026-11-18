static int do_map(unsigned char *out, int map, unsigned char in) {
  switch (in) {
    case '\b':
      if (map & 0x80)
        out[0] = 0x7f;
      else
        out[0] = in;
      return 1;
    case '\n':
      if (map & 0x08) {
        out[0] = '\r';
        return 1;
      } else if (map & 0x10) {
        out[0] = '\r';
        out[1] = '\n';
        return 2;
      } else if (map & 0x20) {
        return 0;
      } else {
        out[0] = in;
        return 1;
      }
    case '\r':
      if (map & 0x01) {
        out[0] = '\n';
        return 1;
      } else if (map & 0x02) {
        out[0] = '\r';
        out[1] = '\n';
        return 2;
      } else if (map & 0x04) {
        return 0;
      } else {
        out[0] = in;
        return 1;
      }
    case 0x7f:
      if (map & 0x40)
        out[0] = '\b';
      else
        out[0] = in;
      return 1;
    default:
      out[0] = in;
      return 1;
  }
}