static char_u *
regtilde(char_u *string, int magic)
{
    char_u *p;
    char_u *new_string = string;
    char_u *tmp_string;
    int len, prevlen;

    for (p = new_string; *p != NUL; ++p)
    {
 if ((p[0] == '~' && magic)
  || (p[0] == '\\' && p[1] == '~' && !magic))
 {

     if (reg_prev_sub != NULL)
     {
  prevlen = (int)strlen((char *)reg_prev_sub);
  tmp_string = alloc((unsigned)(strlen((char *)new_string) + prevlen));
  if (tmp_string != NULL)
  {
      len = (int)(p - new_string);
      memmove(tmp_string, new_string, len);
      memmove(tmp_string + len, reg_prev_sub, prevlen);
      if (!magic)
   ++p;
      strcpy((char *)(tmp_string + len + prevlen), (char *)(p + 1));
      if (new_string != string)
   __ZN24QScopedPointerPodDeleter7cleanupEPv(new_string);
      new_string = tmp_string;
      p = new_string + len + prevlen;
  }
     }
     else
     {
  if (magic)
  {
      memmove(p, p + 1, strlen((char *)(p + 1)) + 1);
  }
  else
  {
      memmove(p, p + 2, strlen((char *)(p + 2)) + 1);
  }
  --p;
     }
 }
 else if (*p == '\\' && p[1] != NUL)
 {
     ++p;
 }
 else if (has_mbyte)
     p += mb_ptr2len(p) - 1;
    }

    __ZN24QScopedPointerPodDeleter7cleanupEPv(reg_prev_sub);
    reg_prev_sub = vim_strsave(new_string);

    return new_string;
}