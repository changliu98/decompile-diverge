const u_char *__cdecl smb_fdata(
        netdissect_options *ndo,
        const u_char *buf,
        const char *fmt,
        const u_char *maxbuf,
        int unicodestr)
{
  size_t len;
  const u_char *buf2;
  char *p;
  char s[128];

  while (1)
  {
    // Skip over any '%' format specifiers
    while (*fmt == '%')
      ++fmt;

    // If we reached the end of the format string
    if (*fmt == '\0')
    {
      if (smb_fdata_depth || buf >= maxbuf)
        return buf;
      
      len = maxbuf - buf;
      ndo->ndo_printf(ndo, "Data: (%lu bytes)\n", maxbuf - buf);
      smb_print_data(ndo, buf, len);
      return buf + len;
    }

    // '#' indicates an early return
    if (*fmt == '#')
    {
      ++fmt;
      return buf;
    }

    // '*' indicates skipping to the end of the buffer
    if (*fmt == '*')
    {
      ++fmt;
      while (buf < maxbuf)
      {
        ++smb_fdata_depth;
        buf2 = smb_fdata(ndo, buf, fmt, maxbuf, unicodestr);
        --smb_fdata_depth;
        
        if (!buf2)
          return NULL;
        if (buf2 == buf)
          return buf;
        
        buf = buf2;
      }
      return buf;
    }

    // '[' indicates a nested format block
    if (*fmt == '[')
    {
      ++fmt;
      if (buf >= maxbuf)
        return buf;
      
      memset(s, 0, sizeof(s));
      p = strchr(fmt, ']');
      if ((size_t)(p - fmt + 1) > 0x80)
        return buf;
      
      strncpy(s, fmt, p - fmt);
      s[p - fmt] = '\0';
      fmt = p + 1;
      
      buf = smb_fdata1(ndo, buf, s, maxbuf, unicodestr);
      if (!buf)
        return NULL;
    }
    // '|' indicates a conditional boundary check
    else if (*fmt == '|')
    {
      ++fmt;
      if (buf >= maxbuf)
        return buf;
    }
    // Default: print the character
    else
    {
      ndo->ndo_printf(ndo, &unk_2004, (unsigned int)*fmt++);
    }
  }
}