int get_number(int colon,int *mouse_used)

{
  int c_00;
  int typed;
  int c;
  int n;
  int *mouse_used_local;
  int colon_local;
  int local_c;
  
  n = 0;
  typed = 0;
  if (mouse_used != (int *)0x0) {
    *mouse_used = 0;
  }
  if (msg_silent == 0) {
    no_mapping = no_mapping + 1;
    allow_keys = allow_keys + 1;
    while( true ) {
      while( true ) {
        while( true ) {
          windgoto(msg_row,msg_col);
          c_00 = safe_vgetc();
          if (9 < c_00 - 0x30U) break;
          n = n * 10 + c_00 + -0x30;
          msg_putchar(c_00);
          typed = typed + 1;
        }
        if ((((c_00 != -0x446b) && (c_00 != -0x50fd)) && (c_00 != -0x626b)) && (c_00 != 8)) break;
        if (0 < typed) {
          msg_puts("\b \b");
          typed = typed + -1;
        }
        n = n / 10;
      }
      if ((mouse_used != (int *)0x0) && (c_00 == -0x2cfd)) {
        *mouse_used = 1;
        n = mouse_row + 1;
        goto LAB_00101445;
      }
      if (((n == 0) && (c_00 == 0x3a)) && (colon != 0)) break;
      if (((c_00 == 3) || (c_00 == 0x1b)) || (c_00 == 0x71)) {
        n = 0;
        goto LAB_00101445;
      }
      if ((c_00 == 0xd) || (c_00 == 10)) goto LAB_00101445;
    }
    stuffcharReadbuff(0x3a);
    if (exmode_active == 0) {
      cmdline_row = msg_row;
    }
    skip_redraw = 1;
    do_redraw = 0;
LAB_00101445:
    no_mapping = no_mapping + -1;
    allow_keys = allow_keys + -1;
    local_c = n;
  }
  else {
    local_c = 0;
  }
  return local_c;
}