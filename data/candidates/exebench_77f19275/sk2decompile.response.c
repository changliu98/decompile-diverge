void extract(unsigned char *buf, int len, int r, int c, int s, int *start,
             int *size) {
  int i, j, r_end, c_end, s_end;
  *start = 0;
  *size = 0;
  if (r <= 0) {
    if (r < 0) return;
    if (c == 0 && s == 0) {
      *size = len;
      return;
    }
    r = 1;
  }
  i = 0;
  for (j = 1; j < r; j++) {
    while (i < len && (buf[i] != 0xCC || buf[i + 1] != 0xBC)) i++;
    if (i >= len) return;
    i += 2;
  }
  r_end = i;
  while (r_end < len && (buf[r_end] != 0xCC || buf[r_end + 1] != 0xBC)) r_end++;
  if (c <= 0) {
    if (c < 0) return;
    if (s == 0) {
      *start = i;
      *size = r_end - i;
      return;
    }
    c = 1;
  }
  for (j = 1; j < c; j++) {
    while (i < len && (buf[i] != 0xCC || buf[i + 1] != 0xBD)) i++;
    if (i >= len) return;
    i += 2;
    if (i > r_end) return;
  }
  c_end = i;
  while (c_end < r_end && (buf[c_end] != 0xCC || buf[c_end + 1] != 0xBD))
    c_end++;
  if (s <= 0) {
    if (s < 0) return;
    *start = i;
    *size = c_end - i;
  }
  for (j = 1; j < s; j++) {
    while (i < r_end && (buf[i] != 0xCC || buf[i + 1] != 0xBE)) i++;
    if (i >= len) return;
    i++;
    if (i > c_end) return;
  }
  s_end = i;
  while (s_end < c_end && (buf[s_end] != 0xCC || buf[s_end + 1] != 0xBE))
    s_end++;
  *start = i;
  *size = (s_end >= c_end) ? c_end - i : s_end - i;
}