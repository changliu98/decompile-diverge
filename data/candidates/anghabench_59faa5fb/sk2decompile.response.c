void scsi_sanitize_inquiry_string(unsigned char *str, int len) {
  int found_null = 0;
  while (len > 0) {
    if (*str == 0) found_null = 1;
    if (found_null || (*str < 0x20 || *str > 0x7e)) *str = 0x20;
    len--;
    str++;
  }
}