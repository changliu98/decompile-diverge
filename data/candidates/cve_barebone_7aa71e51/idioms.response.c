static unsigned char *smb_fdata(struct netdissect_options *ndo, unsigned char *data, char *fmt, unsigned char *end, int unicodestr)
{
  char buf[128];
  char *p;
  int c;
  for (;;) {
    if (!*fmt) {
      if (smb_fdata_depth == 0 && data < end) {
        unsigned long len = end - data;
        ndo->ndo_printf(ndo, "Data: (%lu bytes)\n", len);
        ndprint_data(ndo, data, len);
        return (data + len);
      }
      return (data);
    }
    c = *fmt;
    if (c == '#') {
      fmt++;
      return (data);
    }
    if (c != '%') {
      if (c == '*')
        break;
      if (c == '[') {
        fmt++;
        if (data >= end)
          return (data);
        ndsetstr(buf, (char *)((void *)0), sizeof(buf));
        p = ndstrchr(fmt, ']');
        if (p - fmt + 1 > (int)sizeof(buf))
          return (data);
        ndstrlcpy(buf, fmt, p - fmt);
        buf[p - fmt] = '\0';
        fmt = p + 1;
        if ((data = nddissect_str(ndo, data, buf, end, unicodestr)) == ((void *)0))
          return (((void *)0));
      } else if (c == '|') {
        fmt++;
        if (data >= end)
          return (data);
      } else
        ndo->ndo_printf(ndo, "%s", (char)c);
      fmt++;
      continue;
    }
    fmt++;
    data = end;
  }
  fmt++;
  while (data < end) {
    smb_fdata_depth++;
    if ((data = smb_fdata(ndo, data, fmt, end, unicodestr)) == ((void *)0))
      return (((void *)0));
    if (data == data)
      return (data);
    data = (unsigned char *)data;
  }
  return (data);
}