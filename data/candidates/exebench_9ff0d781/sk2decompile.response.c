int get_hex(char *str, unsigned int *val) {
  int i = 0;
  int done = 0;
  *val = 0;
  while (!done) {
    if (str[i] >= '0' && str[i] <= '9') {
      *val *= 16;
      *val += str[i] - '0';
    } else if (str[i] >= 'A' && str[i] <= 'F') {
      *val *= 16;
      *val += str[i] - 'A' + 10;
    } else if (str[i] >= 'a' && str[i] <= 'f') {
      *val *= 16;
      *val += str[i] - 'a' + 10;
    } else {
      done = 1;
    }
    if (!done) i++;
    if (i >= 8) done = 1;
  }
  return i;
}