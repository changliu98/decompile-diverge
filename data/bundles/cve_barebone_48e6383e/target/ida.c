int __cdecl get_number(int colon, int *mouse_used)
{
  int typed; // [rsp+4h] [rbp-1Ch]
  int c; // [rsp+8h] [rbp-18h]
  int n; // [rsp+Ch] [rbp-14h]

  n = 0;
  typed = 0;
  if ( mouse_used )
    *mouse_used = 0;
  if ( msg_silent )
    return 0;
  ++no_mapping;
  ++allow_keys;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        windgoto(msg_row, msg_col);
        c = safe_vgetc();
        if ( (unsigned int)(c - 48) >= 0xA )
          break;
        n = c + 10 * n - 48;
        msg_putchar(c);
        ++typed;
      }
      if ( c != -17515 && c != -20733 && c != -25195 && c != 8 )
        break;
      if ( typed > 0 )
      {
        msg_puts("\b \b");
        --typed;
      }
      n /= 10;
    }
    if ( mouse_used && c == -11517 )
    {
      *mouse_used = 1;
      n = mouse_row + 1;
      goto LABEL_32;
    }
    if ( !n && c == 58 && colon )
      break;
    if ( c == 3 || c == 27 || c == 113 )
    {
      n = 0;
      goto LABEL_32;
    }
    if ( c == 13 || c == 10 )
      goto LABEL_32;
  }
  stuffcharReadbuff(58);
  if ( !exmode_active )
    cmdline_row = msg_row;
  skip_redraw = 1;
  do_redraw = 0;
LABEL_32:
  --no_mapping;
  --allow_keys;
  return n;
}