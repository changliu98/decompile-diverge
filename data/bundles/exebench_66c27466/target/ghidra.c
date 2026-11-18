char * sgml__utf8_get_char(char *in,int *chr)

{
  int *chr_local;
  char *in_local;
  char *local_10;
  
  if ((((int)*in & 0xe0U) == 0xc0) && (((int)in[1] & 0xc0U) == 0x80)) {
    *chr = ((int)*in & 0x1fU) << 6 | (int)in[1] & 0x3fU;
    local_10 = in + 2;
  }
  else if ((((int)*in & 0xf0U) == 0xe0) &&
          ((((int)in[1] & 0xc0U) == 0x80 && (((int)in[2] & 0xc0U) == 0x80)))) {
    *chr = ((int)*in & 0xfU) << 0xc | ((int)in[1] & 0x3fU) << 6 | (int)in[2] & 0x3fU;
    local_10 = in + 3;
  }
  else if ((((int)*in & 0xf8U) == 0xf0) &&
          (((((int)in[1] & 0xc0U) == 0x80 && (((int)in[2] & 0xc0U) == 0x80)) &&
           (((int)in[3] & 0xc0U) == 0x80)))) {
    *chr = ((int)*in & 7U) << 0x12 | ((int)in[1] & 0x3fU) << 0xc | ((int)in[2] & 0x3fU) << 6 |
           (int)in[3] & 0x3fU;
    local_10 = in + 4;
  }
  else if (((((int)*in & 0xfcU) == 0xf8) && (((int)in[1] & 0xc0U) == 0x80)) &&
          ((((int)in[2] & 0xc0U) == 0x80 &&
           ((((int)in[3] & 0xc0U) == 0x80 && (((int)in[4] & 0xc0U) == 0x80)))))) {
    *chr = ((int)*in & 3U) << 0x18 | ((int)in[1] & 0x3fU) << 0x12 | ((int)in[2] & 0x3fU) << 0xc |
           ((int)in[3] & 0x3fU) << 6 | (int)in[4] & 0x3fU;
    local_10 = in + 5;
  }
  else if ((((int)*in & 0xfeU) == 0xfc) &&
          ((((((int)in[1] & 0xc0U) == 0x80 && (((int)in[2] & 0xc0U) == 0x80)) &&
            (((int)in[3] & 0xc0U) == 0x80)) &&
           ((((int)in[4] & 0xc0U) == 0x80 && (((int)in[5] & 0xc0U) == 0x80)))))) {
    *chr = ((int)*in & 1U) << 0x1e | ((int)in[1] & 0x3fU) << 0x18 | ((int)in[2] & 0x3fU) << 0x12 |
           ((int)in[3] & 0x3fU) << 0xc | ((int)in[4] & 0x3fU) << 6 | (int)in[5] & 0x3fU;
    local_10 = in + 4;
  }
  else {
    *chr = (int)*in;
    local_10 = in + 1;
  }
  return local_10;
}