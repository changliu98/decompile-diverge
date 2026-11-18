int u_get(int *up,char *s)

{
  uchar *t;
  char *s_local;
  int *up_local;
  int local_c;
  
  if ((byte)*s < 0x80) {
    *up = (uint)(byte)*s;
    local_c = 1;
  }
  else if ((byte)*s < 0xc0) {
    local_c = 0;
  }
  else if ((byte)*s < 0xe0) {
    *up = ((byte)*s & 0x1f) << 6 | (byte)s[1] & 0x3f;
    local_c = 0;
    if ((*up & 0xffffff80U) != 0) {
      local_c = 2;
    }
  }
  else if ((byte)*s < 0xf0) {
    *up = (((byte)*s & 0xf) << 6 | (byte)s[1] & 0x3f) << 6 | (byte)s[2] & 0x3f;
    local_c = 0;
    if ((*up & 0xfffff800U) != 0) {
      local_c = 3;
    }
  }
  else if ((byte)*s < 0xf8) {
    *up = ((((byte)*s & 7) << 6 | (byte)s[1] & 0x3f) << 6 | (byte)s[2] & 0x3f) << 6 |
          (byte)s[3] & 0x3f;
    local_c = 0;
    if ((*up & 0xffff0000U) != 0) {
      local_c = 4;
    }
  }
  else if ((byte)*s < 0xfc) {
    *up = (((((byte)*s & 3) << 6 | (byte)s[1] & 0x3f) << 6 | (byte)s[2] & 0x3f) << 6 |
          (byte)s[3] & 0x3f) << 6 | (byte)s[4] & 0x3f;
    local_c = 0;
    if ((*up & 0xffe00000U) != 0) {
      local_c = 5;
    }
  }
  else if ((byte)*s < 0xfe) {
    *up = ((((((byte)*s & 1) << 6 | (byte)s[1] & 0x3f) << 6 | (byte)s[2] & 0x3f) << 6 |
           (byte)s[3] & 0x3f) << 6 | (byte)s[4] & 0x3f) << 6 | (byte)s[5] & 0x3f;
    local_c = 0;
    if ((*up & 0xfc000000U) != 0) {
      local_c = 6;
    }
  }
  else {
    local_c = 0;
  }
  return local_c;
}