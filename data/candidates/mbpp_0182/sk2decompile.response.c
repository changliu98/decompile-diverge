void func0(char *str, char *upper, char *lower, char *digit, char *special) {
  int i, j, k, l, len;
  i = j = k = l = 0;
  len = strlen(str);
  for (int m = 0; m < len; m++) {
    if (isupper(str[m])) {
      upper[i++] = str[m];
    } else if (islower(str[m])) {
      lower[j++] = str[m];
    } else if (isdigit(str[m])) {
      digit[k++] = str[m];
    } else if (str[m] == ',' || str[m] == '.' || str[m] == '!' || str[m] == '?') {
      special[l++] = str[m];
    }
  }
  upper[i] = '\0';
  lower[j] = '\0';
  digit[k] = '\0';
  special[l] = '\0';
}