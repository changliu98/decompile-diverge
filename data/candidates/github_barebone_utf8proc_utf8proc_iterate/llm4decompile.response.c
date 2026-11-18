utf8proc_ssize_t utf8proc_iterate(
  const utf8proc_uint8_t *str, utf8proc_ssize_t strlen, utf8proc_int32_t *dst
) {
  *dst = -1;
  if (!strlen) return 0;
  if (strlen < 0) strlen = 4;
  const utf8proc_uint8_t *u = str;
  const utf8proc_uint8_t *end = str + strlen;
  utf8proc_uint8_t uc = *u;
  if (uc < 0x80) {
    *dst = uc;
    return 1;
  }
  if (uc < 0xc2 || uc > 0xf4) {
    return -3;
  }
  if (uc < 0xe0) {
    if (++u >= end || (*u & 0xc0) != 0x80) {
      return -3;
    }
    *dst = ((uc & 0x1f) << 6) | (*u & 0x3f);
    return 2;
  }
  if (uc < 0xf0) {
    if (++u >= end || (*u & 0xc0) != 0x80) {
      return -3;
    }
    utf8proc_uint32_t uc2 = *u++;
    if (++u >= end || (*u & 0xc0) != 0x80) {
      return -3;
    }
    if (uc == 0xed && uc2 >= 0xa0) {
      return -3;
    }
    uc = ((uc & 0x0f) << 12) | ((uc2 & 0x3f) << 6) | (*u & 0x3f);
    if (uc < 0x800) {
      return -3;
    }
    *dst = uc;
    return 3;
  }
  if (uc < 0xf5) {
    if (++u >= end || (*u & 0xc0) != 0x80) {
      return -3;
    }
    utf8proc_uint32_t uc2 = *u++;
    if (++u >= end || (*u & 0xc0) != 0x80) {
      return -3;
    }
    utf8proc_uint32_t uc3 = *u++;
    if (uc == 0xf0 && uc2 < 0x90) {
      return -3;
    }
    if (uc == 0xf4 && uc2 >= 0x90) {
      return -3;
    }
    *dst = ((uc & 0x07) << 18) | ((uc2 & 0x3f) << 12) | ((uc3 & 0x3f) << 6) | (*u & 0x3f);
    return 4;
  }
  return -3;
}