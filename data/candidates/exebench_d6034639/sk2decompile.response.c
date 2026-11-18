int fatfs_get_sfn_display_name(char *dst, char *src) {
  int i = 0;
  char c;
  while (*src && i < 12) {
    c = *src++;
    if (c == ' ') continue;
    if (c >= 'A' && c <= 'Z') c += 0x20;
    *dst++ = c;
    i++;
  }
  *dst = 0;
  return 1;
}