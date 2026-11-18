void wdc_UtilsDeleteCharFromString(char *str, int len, char c) {
  int j = 0;
  int i;
  if (str == NULL || len == 0) return;
  for (i = 0; i < len && str[i] != '\0'; i++) {
    if (str[i] != c) {
      str[j++] = str[i];
    }
  }
  str[j] = '\0';
}