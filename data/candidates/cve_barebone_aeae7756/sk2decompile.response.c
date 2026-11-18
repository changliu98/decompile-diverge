void ex_history(cmd_t *cmd) {
  int histtype = 0;
  int last_histtype = 0;
  int first = 1;
  int last = -1;
  char_u *p;
  char_u *q;
  int c;
  int start;
  int f;
  int l;
  hist_t *hist;
  p = cmd->args;
  if (hist_count == 0) {
    msg("'history' option is zero");
    return;
  }
  if ((*p < '0' || *p > '9') && *p != '-' && *p != ',') {
    q = p;
    while ((*q >= 'A' && *q <= 'Z') || (*q >= 'a' && *q <= 'z') ||
           vim_strchr((char_u *)"\x3a\x3d\x40\x3e\x2f\x3f", *q) != NULL)
      q++;
    c = *q;
    *q = '\0';
    histtype = get_histtype(p);
    if (histtype == -1) {
      if (strncasecmp(p, "all", strlen(p)) == 0) {
        histtype = 0;
        last_histtype = 4;
      } else {
        *q = c;
        semsg("E488: Trailing characters: %s", p);
        return;
      }
    } else
      last_histtype = histtype;
    *q = c;
  } else
    q = p;
  if (get_list_range(&q, &first, &last) == 0 || *q != '\0') {
    semsg("E488: Trailing characters: %s", q);
    return;
  }
  while (canceled == 0 && histtype <= last_histtype) {
    strcpy(msgbuf, "\n      #  ");
    strcat(strcat(msgbuf, hist_type_name[histtype]), " history");
    msg_puts_title(msgbuf);
    start = hist_start[histtype];
    hist = hist_list[histtype];
    f = first;
    l = last;
    if (f < 0) {
      if (l < hist_count)
        l = 0;
      else
        l = hist[(start + l + 1) % hist_count].num;
    }
    if (l < 0) {
      if (-l > hist_count)
        f = 0;
      else
        f = hist[(start + f + hist_count + 1) % hist_count].num;
    }
    if (start >= 0 && f <= l) {
      int i = start + 1;
      while (canceled == 0) {
        if (i == hist_count) i = 0;
        if (hist[i].cmd != NULL && hist[i].num >= f && hist[i].num <= l) {
          msg_putchar('\n');
          sprintf(msgbuf, "%c%6d  ", i == start ? '>' : ' ', hist[i].num);
          if (vim_strsize(hist[i].cmd) > msg_width - 10) {
            char_u *s = hist[i].cmd;
            char_u *d = msgbuf + strlen(msgbuf);
            trunc_string(s, d, msg_width - 10, 1024 - strlen(msgbuf) + 1);
          } else
            strcat(msgbuf, hist[i].cmd);
          msg_outtrans(msgbuf);
          out_flush();
        }
        if (i == start) break;
        i++;
      }
    }
    histtype++;
  }
}