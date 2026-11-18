char *__cdecl gf_text_get_utf8_line(char *szLine, u32 lineSize, FILE *txt_in, s32 unicode_type)
{
  char szLineConv[2048];
  char *sOK;
  u32 len, j, i;
  char c;
  unsigned __int16 *sptr;

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
        if ((szLine[i + 1] & 0xC0) == 0x80) // Valid UTF-8 continuation byte
        {
          if ((szLine[i] & 0xE0) == 0xC0) // 2-byte UTF-8 sequence
          {
            if (j >= 0x800) goto finalize;
            szLineConv[j++] = szLine[i++];
          }
          else if ((szLine[i] & 0xF0) == 0xE0) // 3-byte UTF-8 sequence
          {
            if (j + 1 >= 0x800) goto finalize;
            szLineConv[j++] = szLine[i++];
            szLineConv[j++] = szLine[i++];
          }
          else if ((szLine[i] & 0xF8) == 0xF0) // 4-byte UTF-8 sequence
          {
            if (j + 2 >= 0x800) goto finalize;
            szLineConv[j++] = szLine[i++];
            szLineConv[j++] = szLine[i++];
            szLineConv[j++] = szLine[i++];
          }
          else
          {
            // Invalid UTF-8 leading byte, skip it
            continue;
          }
        }
        else
        {
          // Non-UTF8 extended ASCII character, convert to 2-byte UTF-8
          if (j >= 0x800) goto finalize;
          szLineConv[j++] = ((szLine[i] >> 6) & 0x03) | 0xC0;
          szLine[i] &= ~0x40; // Modify the lower byte to act as the continuation byte
        }
      }
      
      if (j >= 0x800) goto finalize;
      szLineConv[j++] = szLine[i];
    }
  }
  else
  {
    if (unicode_type == 2)
    {
      // Swap endianness from UTF-16LE to UTF-16BE
      for (i = 0; szLine[i] || szLine[i + 1]; i += 2)
      {
        c = szLine[i + 1];
        szLine[i + 1] = szLine[i];
        szLine[i] = c;
      }
    }
    
    sptr = (unsigned __int16 *)szLine;
    i = gf_utf8_wcstombs(szLineConv, 0x800, (const unsigned __int16 **)&sptr);
    if (i == -1)
      i = 0;
    
    szLineConv[i] = 0;
    strcpy(szLine, szLineConv);
    
    if (unicode_type == 3)
      gf_fgetc(txt_in); // Skip the extra byte (likely consuming a UTF-16LE trailing null)
      
    return sOK;
  }

finalize:
  if (j >= 0x800)
    j = 2047;
    
  szLineConv[j] = 0;
  strcpy(szLine, szLineConv);
  
  return sOK;
}