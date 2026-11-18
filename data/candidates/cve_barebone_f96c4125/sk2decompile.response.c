static void special_keys(char_u *keys) {
  char_u *keys_copy;
  char *key;
  char *dash;
  char buf[64];
  char map[256];
  int len;
  keys_copy = nb_unquote(keys, 0);
  key = strtok(keys_copy, " ");
  while (key != NULL) {
    len = 0;
    dash = strchr(key, '-');
    if (dash != NULL) {
      *dash = '\0';
      while (*key != '\0') {
        switch (*key) {
          case 'A':
          case 'C':
          case 'M':
          case 'S':
            buf[len++] = *key;
            buf[len++] = '-';
            break;
        }
        key++;
      }
      key++;
    }
    if (len + strlen(key) < 64) {
      strcpy(buf + len, key);
      vim_snprintf(map, sizeof(map), "<silent><%s> :nbkey %s<CR>", buf, buf);
      do_map(NULL, (char_u *)map, 1, 0);
    }
    key = strtok(NULL, " ");
  }
  vim_free(keys_copy);
}