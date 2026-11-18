int hex_to_int(char *hex, int *value) {
  int i;
  *value = 0;
  for (i = 0; i < 8; i++) {
    if (hex[i] >= '0' && hex[i] <= '9') {
      *value = *value * 16 + hex[i] - '0';
    } else if (hex[i] >= 'a' && hex[i] <= 'f') {
      *value = *value * 16 + hex[i] - 'a' + 10;
    } else {
      return 0;
    }
  }
  return 1;
}