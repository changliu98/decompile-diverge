void ex_history(int f, char *argv[])
{
  int i; int j; int k; int l;
  int histype1 = 0; int histype2 = 0;
  int hisidx1 = 1; int hisidx2 = -1;
  char *arg = argv[0];
  char *end;
  if (hislen == 0) {
    exerror("'history' option is zero");
    return;
  }
  if (arg[0] >= '0' && arg[0] <= '9' && arg[0] != '-' && arg[0] != ',') {
    end = arg;
    while (1) {
      if (end[0] < 'A' || end[0] > 'Z')
        if (end[0] < 'a' || end[0] > 'z')
          if (!is_in(":=@>?/", end[0]))
            break;
      end++;
    }
    i = *end;
    *end = '\0';
    histype1 = get_histype(arg);
    if (histype1 == -1) {
      if (strneq(arg, "all", strsize(arg))) {
        *end = i;
        exerror("E488: Trailing characters: %s", arg);
        return;
      }
      histype1 = 0;
      histype2 = 4;
    }
    else
      histype2 = histype1;
    *end = i;
  }
  else
    end = arg;
  if (get_hisidx(&end, &hisidx1, &hisidx2) && *end == '\0') {
    for ( ; histype1 <= histype2 && !got_int; histype1++) {
      int hisidx = hisidx[histype1];
      int hisnum;
      histentry *hist = history[histype1];
      if (hisidx1 < 0) {
        if (hisidx1 * -1 > hislen)
          hisnum = 0;
        else
          hisnum = hist[(hisidx + hisidx1 + hislen + 1) % hislen].hisnum;
        hisidx1 = hisnum;
      }
      if (hisidx2 < 0) {
        if (hisidx2 * -1 > hislen)
          hisnum = 0;
        else
          hisnum = hist[(hisidx + hisidx2 + hislen + 1) % hislen].hisnum;
        hisidx2 = hisnum;
      }
      if (hisidx >= 0 && hisidx1 <= hisidx2) {
        for (i = hisidx + 1; !got_int; i++) {
          if (i == hislen)
            i = 0;
          if (hist[i].hisstr
              && hist[i].hisnum >= hisidx1
              && hist[i].hisnum <= hisidx2) {
            exprintf("\n      #  ");
            exprintf(IObuff, "%s history", history_names[histype1]);
            exprintf(IObuff);
            if (Columns - 10 < strsize(IObuff)) {
              char *str = hist[i].hisstr;
              char *p = IObuff;
              char *end = p + strsize(p);
              int room = Columns - 10;
              int len = strsize(IObuff);
              exstrlcpy(str, end, room, 1025 - len);
            }
            else
              exprintf(IObuff, "%s", hist[i].hisstr);
            exprintf("\n");
            exprintf("\n");
          }
          if (i == hisidx)
            break;
        }
      }
    }
  }
  else
    exerror("E488: Trailing characters: %s", end);
}