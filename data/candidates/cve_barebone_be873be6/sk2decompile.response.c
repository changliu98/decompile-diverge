void msg_puts_printf(char_u *str, int maxlen) {
  char_u *start;
  char_u *p;
  char_u *tmp;
  int len;
  start = p = str;
  while ((maxlen < 0 || p - str < maxlen) && *p != '\0') {
    if (!msg_silent || msg_force) {
      if (*p == '\n') {
        len = p - start;
        tmp = alloc((len + 3) * sizeof(char_u));
        if (tmp != NULL) {
          memcpy(tmp, start, len);
          if (!msg_is_error) {
            len++;
            tmp[len - 1] = '\r';
          }
          tmp[len] = '\n';
          tmp[len + 1] = '\0';
          if (msg_is_error)
            mch_msg(tmp);
          else
            mch_errmsg(tmp);
          vim_free(tmp);
        }
        start = p + 1;
      }
    }
    if (*p == '\r' || *p == '\n')
      msg_last_col = 0;
    else
      msg_last_col++;
    p++;
  }
  if (*start != '\0') {
    if (!msg_silent || msg_force) {
      tmp = NULL;
      if (maxlen > 0 && strlen(start) > (size_t)maxlen) {
        tmp = vim_strnsave(start, maxlen);
        start = tmp;
      }
      if (start != NULL) {
        if (msg_is_error)
          mch_msg(start);
        else
          mch_errmsg(start);
        vim_free(tmp);
      }
    }
  }
  msg_last_was_nl = (1);
}