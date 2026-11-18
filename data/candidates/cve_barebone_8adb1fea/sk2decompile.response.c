void ga_concat_shorten_esc(char_u *buf, char *str) {
  char *p, *start;
  int count, len;
  int c;
  char tmp[65];
  if (str == NULL)
    ga_concat(buf, "NULL");
  else {
    for (start = str; *start != '\0'; start = p) {
      count = 1;
      p = start;
      c = mb_ptr2char_adv(&p);
      len = p - start;
      while (*p != '\0' && mb_ptr2char(p) == c) {
        count++;
        p += len;
      }
      if (count > 20) {
        ga_concat(buf, "\\[");
        ga_concat_esc(buf, start, len);
        ga_concat(buf, " occurs ");
        vim_snprintf(tmp, sizeof(tmp), "%d", count);
        ga_concat(buf, tmp);
        ga_concat(buf, " times]");
        start = p - 1;
      } else
        ga_concat_esc(buf, start, len);
    }
  }
}