size_t modp_rtrim(char *str, size_t len) {
  while (len > 0) {
    char c = str[len - 1];
    if (c != ' ' && c != '\n' && c != '\t' && c != '\r') {
      break;
    }
    str[--len] = '\0';
  }
  return len;
}