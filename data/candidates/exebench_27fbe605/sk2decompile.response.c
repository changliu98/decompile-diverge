int vpf_str_to_num(const char *str, int *num) {
  int n = 0;
  const char *start = str;
  while (*str) {
    if (*str < '0' || *str > '9') break;
    n = n * 10 + (*str - '0');
    str++;
  }
  *num = n;
  return str - start;
}