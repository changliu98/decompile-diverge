int conv_hstring(char *str, unsigned int *val) {
  int i = 0;
  *val = 0;
  while ((str[i] >= '0' && str[i] <= '9') ||
         (str[i] >= 'a' && str[i] <= 'f') && i < 9) {
    if (str[i] >= '0' && str[i] <= '9')
      *val = *val * 16 + (str[i++] - '0');
    else
      *val = *val * 16 + (str[i++] - 'a' + 10);
  }
  return i;
}