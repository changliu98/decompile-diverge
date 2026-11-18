char *__cdecl gf_text_get_utf8_line(char *szLine, u32 lineSize, FILE *txt_in, s32 unicode_type)
{
  char c;
  unsigned __int16 *sptr;
  char szLineConv[2048];
  char *sOK;
  u32 len, j, i;

  memset(szLine, 0, lineSize);
  sOK = gf_fgets(szLine, lineSize, txt_in);
  if (!sOK)
    return NULL;

  if (unicode_type <= 1)
  {
    j = 0;
    len = strlen(szLine);
    for (i = 0; i < len; ++i)
    {
      if (unicode_type == 0 && (szLine[i] & 0x80) != 0)
      {
        if ((szLine[i + 1] & 0xC0) == 0x80)
        {
          if ((szLine[i] & 0xE0) == 0xC0)
          {
            szLineConv[j++] = szLine[i++];
          }
          else if ((szLine[i] & 0xF0) == 0xE0)
          {
            szLineConv[j++] = szLine[i++];
            szLineConv[j++] = szLine[i++];
          }
          else
          {
            if ((szLine[i] & 0xF8) != 0xF0)
            {
              continue;
            }
            szLineConv[j++] = szLine[i++];
            szLineConv[j++] = szLine[i++];
            szLineConv[j++] = szLine[i++];
          }
        }
        else
        {
          szLineConv[j++] = ((szLine[i] >> 6) & 0x03) | 0xC0;
          szLine[i] &= ~0x40u;
        }
      }
      szLineConv[j++] = szLine[i];
      if (j >= 0x7FF)
        break;
    }
    szLineConv[j] = 0;
    strcpy(szLine, szLineConv);
    return sOK;
  }

  if (unicode_type == 2)
  {
    for (i = 0; szLine[i] || szLine[i + 1]; i += 2)
    {
      c = szLine[i + 1];
      szLine[i + 1] = szLine[i];
      szLine[i] = c;
    }
  }

  sptr = (unsigned __int16 *)szLine;
  i = gf_utf8_wcstombs(szLineConv, 0x800uLL, (const unsigned __int16 **)&sptr);
  if (i == -1)
    i = 0;
  szLineConv[i] = 0;
  strcpy(szLine, szLineConv);

  if (unicode_type == 3)
    gf_fgetc(txt_in);

  return sOK;
}