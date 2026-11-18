char *__concat(char **strs, int n) {
  int i, len;
  char *ret;
  len = 0;
  for (i = 0; i < n; i++) len += strlen(strs[i]);
  ret = malloc(len + 1);
  if (ret == NULL) return NULL;
  ret[0] = '\0';
  for (i = 0; i < n; i++) strcat(ret, strs[i]);
  return ret;
}