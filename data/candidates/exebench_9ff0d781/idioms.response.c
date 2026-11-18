int get_hex(char *str, unsigned int *num)
{
  int i = 0;
  int done = 0;
  *num = 0;
  while (!done) {
    if (str[i] >= '0' && str[i] <= '9') {
      *num *= 16;
      *num += str[i] - '0';
    }
    else if (str[i] >= 'A' && str[i] <= 'F') {
      *num *= 16;
      *num += str[i] - 'A' + 10;
    }
    else if (str[i] >= 'a' && str[i] <= 'f') {
      *num *= 16;
      *num += str[i] - 'a' + 10;
    }
    else {
      done = 1;
    }
    if (!done)
      i++;
    if (i >= 8)
      done = 1;
  }
  return i;
}