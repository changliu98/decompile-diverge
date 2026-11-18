char *string_copy(char *dest, const char *src) {
  char *s, *d;
  if (src == NULL || dest == NULL) return NULL;
  s = (char *)src;
  d = dest;
  while (*s) *d++ = *s++;
  *d = '\0';
  return dest;
}