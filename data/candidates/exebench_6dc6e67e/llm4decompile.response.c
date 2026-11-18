void copia(char *dest, char *source) {
  while (*source) {
    *dest = *source;
    dest++;
    source++;
  }
  *dest = '\0';
}