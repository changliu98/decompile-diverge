void ck_decrypt(char *s) {
  while (*s) {
    if (*s != 'p' && *s != '\\' && *s != 'S') *s ^= 0x0f;
    s++;
  }
}