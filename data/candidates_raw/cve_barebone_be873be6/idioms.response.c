void msg_out(char *str, int maxlen)
{
     char *s = str;
     char *p = str;
     char *buf;
     int len;
     char *tofree = (char *)((void *)0);
     int do_out;
     for (;;) {
          if (maxlen >= 0 && (int)(s - str) >= maxlen)
        do_out = 0;
          else
        do_out = *s ? 1 : 0;
          if (!do_out)
        break;
          if (!silent_mode || p_verbose)
        if (*s == '\n') {
      len = s - p;
      if ((buf = (char *)emalloc(len + 3)) != ((void *)0)) {
    strlcpy(buf, p, len + 1);
    if (!info_message)
        buf[len++] = '\r';
    buf[len] = '\n';
    buf[len + 1] = '\0';
    if (info_message)
        msg_out_info(buf);
    else
        msg_out_err(buf);
    free(buf);
      }
      p = s + 1;
        }
          if (*s == '\r' || *s == '\n')
        msg_col = 0;
          else
        msg_col++;
          s++;
     }
     if (*p && (!silent_mode || p_verbose)) {
   if (maxlen > 0 && msg_strlen(p) > maxlen) {
        tofree = msg_strndup(p, maxlen);
        p = tofree;
   }
   if (p) {
        if (info_message)
     msg_out_info(p);
        else
     msg_out_err(p);
        free(tofree);
   }
     }
     msg_didout = 1;
}