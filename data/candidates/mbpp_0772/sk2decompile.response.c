char *func0(char *str, int len) {
  char buf[1000];
  char *ret;
  char *tok;
  size_t l;
  strncpy(buf, str, 1000);
  buf[1000 - 1] = 0;
  ret = malloc(strlen(str) + 1);
  if (ret == NULL) {
    perror("malloc failed");
    exit(1);
  }
  ret[0] = 0;
  tok = strtok(buf, " ");
  while (tok != NULL) {
    if (strlen(tok) != len) {
      strcat(ret, tok);
      strcat(ret, " ");
    }
    tok = strtok(NULL, " ");
  }
  l = strlen(ret);
  if (l > 0 && ret[l - 1] == ' ') {
    ret[l - 1] = 0;
  }
  return ret;
}