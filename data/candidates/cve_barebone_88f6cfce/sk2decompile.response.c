void append_command(char *cmd) {
  char *p, *q;
  char *s = cmd;
  strcat(command, ": ");
  p = command;
  q = p + strlen(command);
  while (*s && (q - command < 1018)) {
    if (utf8) {
      if (*s == 0xC2 && *(s + 1) == 0xA0) {
        s += (utf8 ? 2 : 1);
        strcpy(q, "<a0>");
        q += 4;
        continue;
      }
    } else {
      if (*s == 0xA0) {
        s += (utf8 ? 2 : 1);
        strcpy(q, "<a0>");
        q += 4;
        continue;
      }
    }
    if (mb_copy_char)
      mb_copy_char(&s, &q);
    else
      *q++ = *s++;
  }
  *q = '\0';
}