void __cdecl msg_puts_printf(char_u *str, int maxlen)
{
  char_u *tofree;
  int n;
  char_u *p;
  char_u *buf;
  char_u *s;

  s = str;
  p = str;
  while (1)
  {
    bool continue_loop;
    if (maxlen < 0)
      continue_loop = (*s != 0);
    else
      continue_loop = ((s - str < maxlen) && (*s != 0));

    if (!continue_loop)
      break;

    if ((!silent_mode || p_verbose) && *s == '\n')
    {
      n = s - p;
      buf = alloc(n + 3);
      if (buf)
      {
        memcpy(buf, p, n);
        if (!info_message)
        {
          buf[n] = '\r';
          n++;
        }
        buf[n] = '\n';
        buf[n + 1] = '\0';
        
        if (info_message)
          mch_msg((char *)buf);
        else
          mch_errmsg((char *)buf);
          
        vim_free(buf);
      }
      p = s + 1;
    }

    if (*s == '\r' || *s == '\n')
      msg_col = 0;
    else
      ++msg_col;
      
    ++s;
  }

  if (*p && (!silent_mode || p_verbose))
  {
    tofree = NULL;
    if (maxlen > 0 && strlen((const char *)p) > maxlen)
    {
      tofree = vim_strnsave(p, maxlen);
      p = tofree;
    }
    if (p)
    {
      if (info_message)
        mch_msg((char *)p);
      else
        mch_errmsg((char *)p);
      vim_free(tofree);
    }
  }
  msg_didout = 1;
}