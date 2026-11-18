int paste(enum paste_mode mode, int drop, struct garray *ga)
{
  char buf[-1];
  int i = 0;
  char *end = get_end_of_name(name);
  int ret_char = -1;
  int save_allow_keys = allow_keys;
  int save_paste = p_paste;
  if (end && get_key(end) >= (0x41))
    end = ((void *)0);
  no_mapping++;
  allow_keys = 0;
  if (!p_paste)
    set_paste("paste", 1, ((void *)0), 0);
  while (end || got_ex())
  {
    int c = get_ex_key();
    int is_backspace = 1;
    if (c == (0x1001))
      continue;
    if (c == (0x1002))
      continue;
    if (c == (0x1003))
      continue;
    if (c == 0 || got_int || (ex_normal_busy > 0 && c == '\c'))
      break;
    if (has_mbyte)
      i += mb_char2bytes(c, &buf[i]);
    else
      buf[i++] = c;
    buf[i] = '\0';
    if (end && !strnstr(buf, end, i))
    {
      if (end[i] == '\0')
        break;
    }
    else
    {
      if (!drop)
      {
        switch (mode)
        {
          case PASTE_INSERT:
            if (ex_insert() == 1)
            {
              c = buf[0];
              if (i == 1 && (c == '\r' || c == '\n'))
                ex_insert_char(c);
              else
              {
                ex_insert_str(buf, i);
                ex_insert_end(buf, i);
              }
            }
            break;
          case PASTE_CMDLINE:
            ex_cmdline(buf, i, 1);
            break;
          case PASTE_EX:
            if (ga && ex_ga_ok(ga, i) == 1)
            {
              ex_ga_put(ga->ga_data + ga->ga_len, buf, i);
              ga->ga_len += i;
            }
            break;
          case PASTE_ONE_CHAR:
            if (ret_char == -1)
            {
              if (has_mbyte)
                ret_char = mb_ptr2char(buf);
              else
                ret_char = buf[0];
            }
            break;
        }
      }
      i = 0;
    }
  }
  no_mapping--;
  allow_keys = save_allow_keys;
  if (!save_paste)
    set_paste("paste", 0, ((void *)0), 0);
  return ret_char;
}