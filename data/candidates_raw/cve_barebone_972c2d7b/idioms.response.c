char *regtilde(char *str, int magic)
{
  char *p;
  char *newstr;
  char *newstr2;
  int len; int prevlen;
  newstr = str;
  for (p = newstr; *p != '\0'; p++)
  {
    if ((*p == '~' && magic) || (*p == '\\' && p[1] == '~' && !magic))
    {
      if (reg_prev_sub != ((void *)0))
      {
        prevlen = strlen(reg_prev_sub);
        newstr2 = alloc(prevlen + strlen(newstr));
        if (newstr2 == ((void *)0))
          continue;
        len = p - newstr;
        memmove(newstr2, newstr, len);
        memmove(newstr2 + len, reg_prev_sub, prevlen);
        if (!magic)
          p++;
        strcpy(newstr2 + len + prevlen, p + 1);
        if (newstr != str)
          free(newstr);
        newstr = newstr2;
        p = newstr + len + prevlen;
      }
      else
      {
        if (magic)
          memmove(p, p + 1, strlen(p + 1) + 1);
        else
          memmove(p, p + 2, strlen(p + 2) + 1);
      }
      p--;
    }
    else
    {
      if (*p == '\\' && p[1] != '\0')
        p++;
      if (has_mbyte)
        p += (int)(mb_ptr2len(p)-1);
    }
  }
  free(reg_prev_sub);
  reg_prev_sub = vim_strsave(newstr);
  return (newstr);
}