int c_decrypt(char *str) {
  while (*str) {
    *str -= 13;
    str++;
  }
  return 0;
}