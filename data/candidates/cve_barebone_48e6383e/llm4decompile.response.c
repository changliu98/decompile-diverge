int
get_number(int colon, int *mouse_used)
{
 int c;
 int n;
 int typed;

 n = 0;
 typed = 0;
 if (mouse_used != NULL)
  *mouse_used = 0;

 if (msg_silent)
  return 0;

 no_mapping++;
 allow_keys++;
 for (;;) {
  windgoto(msg_row, msg_col);
  c = safe_vgetc();
  if (c >= '0' && c <= '9') {
   n = n * 10 + c - '0';
   msg_putchar(c);
   typed++;
   continue;
  }
  if (c == ('C' & 0x3f) || c == ('D' & 0x3f) || c == ('H' & 0x3f) ||
      c == '\b') {
   if (typed > 0) {
    msg_puts("\b \b");
    typed--;
   }
   n = n / 10;
   continue;
  }
  if (mouse_used != NULL && c == ('u' & 0x3f)) {
   *mouse_used = 1;
   n = mouse_row + 1;
   break;
  }
  if (n == 0 && c == ':' && colon) {
   stuffcharReadbuff(c);
   if (!exmode_active)
    cmdline_row = msg_row;
   skip_redraw = 1;
   do_redraw = 0;
   break;
  }
  if (c == 0x03 || c == '\033' || c == 'q') {
   n = 0;
   break;
  }
  if (c == '\r' || c == '\n')
   break;
 }
 no_mapping--;
 allow_keys--;
 return n;
}