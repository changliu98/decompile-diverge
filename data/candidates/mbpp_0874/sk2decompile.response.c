bool func0(char* s, char* t) {
  int s_len = strlen(s);
  int t_len = strlen(t);
  if (s_len % t_len != 0) {
    return false;
  }
  for (int i = 0; i < s_len; i++) {
    if (s[i] != t[i % t_len]) {
      return false;
    }
  }
  return true;
}