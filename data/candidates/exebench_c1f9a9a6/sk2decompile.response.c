int parse_uuid(const char *str, unsigned char *uuid) {
  int i, n, len;
  char c;
  len = 0;
  for (i = 0; i < 4; i++) uuid[i] = 0;
  while ((c = *str++)) {
    if (c >= '0' && c <= '9')
      n = c - '0';
    else if (c >= 'a' && c <= 'f')
      n = c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
      n = c - 'A' + 10;
    else if (strchr(":. -", c))
      continue;
    else
      return 0;
    if (len < 32) {
      uuid[len / 8] *= 16;
      uuid[len / 8] += n;
    }
    len++;
  }
  return len == 32;
}