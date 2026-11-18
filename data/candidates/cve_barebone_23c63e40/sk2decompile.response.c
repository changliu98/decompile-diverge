char *get_next_file(FILE *fp, char *line) {
  char *ret;
  ret = fgets(line, 1024, fp);
  if (ret == NULL) return NULL;
  if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
  return ret;
}