int32_t readUTF8(char *in,int len,int l,int *utf8len)

{
  int32_t ret;
  int *utf8len_local;
  int l_local;
  int len_local;
  char *in_local;
  
  ret = 0;
  if (((l < len + -1) && (((int)in[l] & 0xe0U) == 0xc0)) && (((int)in[l + 1] & 0xc0U) == 0x80)) {
    *utf8len = 2;
    ret = ((int)in[l + 1] & 0x3fU) + ((int)in[l] & 0x1fU) * 0x40;
    if ((uint)ret < 0x80) {
      ret = 0;
    }
  }
  else if (((l < len + -2) && (((int)in[l] & 0xf0U) == 0xe0)) &&
          ((((int)in[l + 1] & 0xc0U) == 0x80 && (((int)in[l + 2] & 0xc0U) == 0x80)))) {
    *utf8len = 3;
    ret = ((int)in[l + 2] & 0x3fU) + (((int)in[l + 1] & 0x3fU) + ((int)in[l] & 0xfU) * 0x40) * 0x40;
    if ((uint)ret < 0x800) {
      ret = 0;
    }
  }
  else if (((l < len + -3) && (((int)in[l] & 0xf8U) == 0xf0)) &&
          ((((int)in[l + 1] & 0xc0U) == 0x80 &&
           ((((int)in[l + 2] & 0xc0U) == 0x80 && (((int)in[l + 3] & 0xc0U) == 0x80)))))) {
    *utf8len = 4;
    ret = ((int)in[l + 3] & 0x3fU) +
          (((int)in[l + 2] & 0x3fU) + (((int)in[l + 1] & 0x3fU) + ((int)in[l] & 7U) * 0x40) * 0x40)
          * 0x40;
    if ((uint)ret < 0x10000) {
      ret = 0;
    }
  }
  return ret;
}