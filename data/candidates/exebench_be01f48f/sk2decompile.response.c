char *my_strcpy(char *dest, const char *src) {
  char *tmp = dest;
  char c;
  do {
    c = *src++;
    *tmp++ = c;
  } while (c != '\0');
  return dest;
}