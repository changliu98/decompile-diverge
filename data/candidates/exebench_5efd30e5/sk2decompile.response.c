int stringToInt(unsigned int *value, char *str) {
  *value = 0;
  while (*str) {
    if (*str < '0' || *str > '9') return -1;
    *value = *value * 10 + *str - '0';
    str++;
  }
  return 0;
}