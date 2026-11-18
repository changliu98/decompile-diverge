char *trim(char *str, const char *what) {
  char *end;
  if (str == NULL) return NULL;
  end = index(str, '\0') - 1;
  while (end >= str && index(what, *end) != NULL) {
    *end = '\0';
    end--;
  }
  return str;
}