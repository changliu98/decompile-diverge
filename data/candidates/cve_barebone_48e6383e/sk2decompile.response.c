int get_number(int allow_colon, int *p_abort) {
  int ch, num = 0, digits = 0;
  if (p_abort) *p_abort = 0;
  if (is_in_search) return 0;
  msg_line++;
  msg_col++;
  for (;;) {
    windgoto(cur_row, cur_col);
    ch = safe_vgetc();
    if (ch >= '0' && ch <= '9') {
      num = num * 10 + ch - '0';
      msg_putchar(ch);
      digits++;
    } else if (ch == -17515 || ch == -20733 || ch == -25195 || ch == '\b') {
      if (digits > 0) {
        msg_puts("\b \b");
        digits--;
      }
      num /= 10;
    } else if (p_abort && ch == -11517) {
      *p_abort = 1;
      num = INT_MAX + 1;
      break;
    } else if (allow_colon && ch == ':') {
      stuffcharReadbuff(ch);
      if (!search_is_active) search_row = cur_row;
      search_is_active = 1;
      search_is_reverse = 0;
      break;
    } else if (ch == '\003' || ch == 27 || ch == 'q') {
      num = 0;
      break;
    } else if (ch == '\r' || ch == '\n')
      break;
  }
  msg_line--;
  msg_col--;
  return num;
}