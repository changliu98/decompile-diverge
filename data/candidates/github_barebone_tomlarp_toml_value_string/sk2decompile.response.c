int toml_value_string(const char *str, char **out, int *len) {
  int multiline = 0;
  const char *s, *e;
  int q;
  int slen;
  *out = NULL;
  if (str == NULL) return -1;
  q = str[0];
  slen = strlen(str);
  if (q != '\'' && q != '"') return -1;
  if (str[1] == q && str[2] == q) {
    multiline = 1;
    s = str + 3;
    e = str + slen - 3;
    if (s > e || e[0] != q || e[1] != q || e[2] != q) return -1;
    if (s[0] == '\n')
      s++;
    else if (s[0] == '\r' && s[1] == '\n')
      s += 2;
  } else {
    s = str + 1;
    e = str + slen - 1;
    if (s > e || e[0] != q) return -1;
  }
  if (q == '\'')
    *out = norm_lit_str(s, e - s, len, multiline, 0, 0);
  else
    *out = norm_basic_str(s, e - s, len, multiline, 0, 0);
  return *out ? 0 : -1;
}