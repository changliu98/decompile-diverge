static int
get_number(
    int colon,
    int *mouse_used)
{
    int c;
    int n = 0;
    int typed = 0;

    if (mouse_used != NULL)
 *mouse_used = 0;

    if (msg_silent)
    {
 n = 0;
    }
    else
    {
 no_mapping++;
 allow_keys++;

 for (;;)
 {
     windgoto(msg_row, msg_col);
     c = safe_vgetc();
     if (isdigit(c))
     {
  n = n * 10 + c - '0';
  msg_putchar(c);
  typed++;
     }
     else if (c == 0xbb95 || c == 0xaf03 || c == 0x9d95 || c == 0x08)
     {

  if (typed > 0)
  {
      msg_puts("\b \b");
      typed--;
  }
  n /= 10;
     }
     else if (mouse_used != NULL && c == 0xd303)
     {
  *mouse_used = 1;
  n = mouse_row + 1;
  break;
     }
     else if (n == 0 && c == ':')
     {
  if (colon)
  {
      stuffcharReadbuff(':');
      if (!exmode_active)
   cmdline_row = msg_row;
      skip_redraw = TRUE;
      do_redraw = FALSE;
  }
  break;
     }
     else if (c == '\003' || c == '\033' || c == 'q')
     {
  n = 0;
  break;
     }
     else if (c == '\r' || c == '\n')
  break;
     else
  break;
 }

 no_mapping--;
 allow_keys--;
    }

    return n;
}