void __cdecl append_command(char_u *cmd)
{
  char_u *d = IObuff + strlen(IObuff);
  char_u *s = cmd;

  strcat(IObuff, ": ");

  while (*s && (d - (char_u *)IObuff < 1018))
  {
    if (enc_utf8)
    {
      if (*s == 194 && s[1] == 160)
      {
        s += 2;
        strcpy((char *)d, "<a0>");
        d += 4;
        continue;
      }
    }
    else if (*s == 160)
    {
      s += 1;
      strcpy((char *)d, "<a0>");
      d += 4;
      continue;
    }

    if (has_mbyte)
    {
      mb_copy_char(&s, &d);
    }
    else
    {
      *d++ = *s++;
    }
  }
  *d = 0;
}