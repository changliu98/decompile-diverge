int getmsg(int colon, int *mouse_used)
{
  int c;
  int n = 0;
  int typed = 0;
  if (mouse_used)
    *mouse_used = 0;
  if (msg_silent)
    return (0);
  no_mapping++;
  allow_keys++;
  for (;;) {
    msgpos(msg_row, msg_col);
    c = getch();
    if (c >= '0' && c <= '9') {
      n = n * 10 + c - '0';
      putch(c);
      typed++;
    } else if (c == -17515 || c == -20733 || c == -25195 || c == '\b') {
      if (typed > 0) {
        putch("\b \b");
        typed--;
      }
      n /= 10;
    } else if (mouse_used && c == -11517) {
      *mouse_used = 1;
      n = mouse_row + 1;
      break;
    } else if (n == 0 && c == ':' && colon) {
      putch(':');
      if (!exmode_active)
        cmdline_row = msg_row;
      skip_redraw = 1;
      do_redraw = 0;
      break;
    } else if (c == '\003' || c == '\033' || c == 'q') {
      n = 0;
      break;
    } else if (c == '\r' || c == '\n')
      break;
  }
  no_mapping--;
  allow_keys--;
  return (n);
}