void special_keys(char *arg)
{
  char *save;
  char *tok;
  char *sep;
  char key[64];
  char cmd[256];
  int i;
  arg = unquote(arg, ((void *)0));
  for (tok = get_next_arg(arg); tok != ((void *)0); tok = get_next_arg(((void *)0))) {
    i = 0;
    if ((sep = strchr(tok, '-'))) {
      *sep = '\0';
      for (; *tok != '\0'; tok++) {
        int c = *tok;
        if (c == 'A' || c == 'C' || c == 'M' || c == 'S') {
          key[i++] = *tok;
          key[++i] = '-';
        }
      }
      tok++;
    }
    if (i + strlen(tok) < sizeof(key)) {
      strlcpy(&key[i], tok, sizeof(key) - i);
      snprintf(cmd, sizeof(cmd), "<silent><%s> :nbkey %s<CR>", key, key);
      ex_command(0, cmd, 1, 0);
    }
  }
  free(arg);
}