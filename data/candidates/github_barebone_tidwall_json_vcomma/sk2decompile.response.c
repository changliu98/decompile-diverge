static int vcomma(const char *str, int len, int pos, char end) {
  if (pos == len) return -(pos + 1);
  if (str[pos] == ',') return pos;
  while (str[pos] == ' ' || str[pos] == '\t' || str[pos] == '\n' ||
         str[pos] == '\r') {
    pos++;
    if (pos >= len) return -(pos + 1);
  }
  if (str[pos] == ',') return pos;
  if (str[pos] == end) return pos;
  return -(pos + 1);
}