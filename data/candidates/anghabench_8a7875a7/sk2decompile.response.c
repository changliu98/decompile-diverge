static unsigned char hex_char(unsigned char c) {
  if (c < 10) {
    return '0' + c;
  } else if (c < 16) {
    return 'a' + (c - 10);
  } else {
    return '?';
  }
}