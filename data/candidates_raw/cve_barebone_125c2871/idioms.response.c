int json_to_str(unsigned char *data, unsigned char *data_end, char *name, char *dst, int dst_size)
{
  int namelen = json_namelen(name);
  int len;
  int size;
  int type;
  unsigned long long i;
  unsigned long long i2;
  unsigned char *p;
  unsigned char *p2;
  for (;;) {
    int is_end = 0;
    if (*data != 0x03)
      is_end = (data < data_end);
    if (is_end) {
      len = json_getlen(data, data_end);
      if (len < 0)
        len = data_end - data;
      data += len;
    } else
      break;
  }
  if (data_end - data < 3)
    return -1;
  data++;
  for (;;) {
    p = data;
    data += 2;
    size = (data[-1] | (data[-2] << 8));
    if (size == 0)
      return -1;
    if (size < 0 || data + size > data_end)
      return -1;
    data += size;
    if (size == namelen && !json_strcmp(data - size, name, namelen))
      break;
    len = json_getlen(data, data_end);
    if (len < 0 || data + len > data_end)
      return -1;
    data += len;
  }
  type = *data++;
  if (type == 0) {
    i = ((unsigned long long)(data[0]) |
        ((unsigned long long)(data[1]) << 8) |
        ((unsigned long long)(data[2]) << 16) |
        ((unsigned long long)(data[3]) << 24) |
        ((unsigned long long)(data[4]) << 32) |
        ((unsigned long long)(data[5]) << 40) |
        ((unsigned long long)(data[6]) << 48) |
        ((unsigned long long)(data[7]) << 56));
    i = __builtin_bswap64(i);
    json_snprintf(dst, dst_size, "%g", (double) i);
  } else if (type == 1)
    json_snprintf(dst, dst_size, "%s", *data ? "true" : "false");
  else if (type == 2) {
    p2 = data;
    data += 2;
    len = (data[-1] | (data[-2] << 8));
    if (len + 1 > dst_size)
      size = dst_size;
    else
      size = len + 1;
    json_strlcpy(dst, (char *)data, size);
  } else
    return -1;
  return 0;
}