int __cdecl get_number(int colon, int *mouse_used)
{
  int typed = 0;
  int c;
  int n = 0;

  if (mouse_used)
    *mouse_used = 0;
  if (msg_silent)
    return 0;

  ++no_mapping;
  ++allow_keys;

  while (1)
  {
    windgoto(msg_row, msg_col);
    c = safe_vgetc();

    // Check for digit characters ('0'-'9')
    if ((unsigned int)(c - '0') < 10)
    {
      n = c + 10 * n - '0';
      msg_putchar(c);
      ++typed;
      continue;
    }

    // Check for backspace/delete keys
    if (c == -17515 || c == -20733 || c == -25195 || c == 8)
    {
      if (typed > 0)
      {
        msg_puts("\b \b");
        --typed;
      }
      n /= 10;
      continue;
    }

    // Check for mouse click
    if (mouse_used && c == -11517)
    {
      *mouse_used = 1;
      n = mouse_row + 1;
      break;
    }

    // Check for ':' input if colon is allowed
    if (!n && c == ':' && colon)
    {
      stuffcharReadbuff(':');
      if (!exmode_active)
        cmdline_row = msg_row;
      skip_redraw = 1;
      do_redraw = 0;
      break;
    }

    // Check for cancellation (Ctrl-C, ESC, 'q')
    if (c == 3 || c == 27 || c == 113)
    {
      n = 0;
      break;
    }

    // Check for confirmation (Enter)
    if (c == 13 || c == 10)
      break;
  }

  --no_mapping;
  --allow_keys;
  return n;
}