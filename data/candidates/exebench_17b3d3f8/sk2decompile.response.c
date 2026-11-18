void gsm_hex_from_byte(char *s, int c) {
  s[0] = hex_digits[(c >> 4) & 0x0f];
  s[1] = hex_digits[c & 0x0f];
}