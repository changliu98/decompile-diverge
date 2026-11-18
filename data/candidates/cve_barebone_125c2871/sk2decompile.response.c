int ff_amf_get_field_value(const unsigned char *p, const unsigned char *end,
                           const char *field, char *value, int size) {
  int len, len2, type, flen;
  flen = strlen(field);
  while (*p != 0x03 && p < end) {
    len = ff_amf_tag_size(p, end);
    if (len < 0) len = end - p;
    p += len;
  }
  if (end - p < 3) return -1;
  p++;
  while (1) {
    len = p[0] << 8 | p[1];
    p += 2;
    if (len == 0) return -1;
    if (len < 0 || len >= end - p) return -1;
    p += len;
    if (len == flen && !memcmp(p - len, field, flen)) break;
    len2 = ff_amf_tag_size(p, end);
    if (len2 < 0 || len2 >= end - p) return -1;
    p += len2;
  }
  type = *p++;
  if (type == 0) {
    double d = *(double *)p;
    snprintf(value, size, "%g", d);
  } else if (type == 1) {
    snprintf(value, size, "%s", *p ? "true" : "false");
  } else if (type == 2) {
    len = p[0] << 8 | p[1];
    p += 2;
    av_strlcpy(value, (char *)p, len + 1 > size ? size : len + 1);
  } else {
    return -1;
  }
  return 0;
}