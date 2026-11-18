char *_glp_lib_trim_spaces(const char *str) {
  char *tmp;
  unsigned int len, i, j;
  if (str == NULL) return NULL;
  len = strlen(str);
  tmp = malloc(len + 1);
  if (tmp == NULL) return NULL;
  i = 0;
  j = 0;
  int flag = 0;
  while (str[i] != '\0') {
    if (str[i] == ' ') {
      if (!flag) {
        tmp[j++] = ' ';
        flag = 1;
      }
    } else {
      tmp[j++] = str[i];
      flag = 0;
    }
    i++;
  }
  tmp[j] = '\0';
  return tmp;
}