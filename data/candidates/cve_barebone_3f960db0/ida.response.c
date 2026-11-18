char *__cdecl gf_text_get_utf8_line(char *szLine, u32 lineSize, FILE *txt_in, s32 unicode_type)
{
  char c; // [rsp+7h] [rbp-849h]
  unsigned __int16 *sptr; // [rsp+8h] [rbp-848h] BYREF
  char szLineConv[2048]; // [rsp+10h] [rbp-840h] BYREF
  char *sOK; // [rsp+818h] [rbp-38h]
  u32 len; // [rsp+820h] [rbp-30h]
  u32 j; // [rsp+824h] [rbp-2Ch]
  u32 i; // [rsp+828h] [rbp-28h]
  s32 unicode_typea; // [rsp+82Ch] [rbp-24h]
  FILE *txt_ina; // [rsp+830h] [rbp-20h]
  u32 lineSizea; // [rsp+83Ch] [rbp-14h]
  char *szLinea; // [rsp+840h] [rbp-10h]

  szLinea = szLine;
  lineSizea = lineSize;
  txt_ina = txt_in;
  unicode_typea = unicode_type;
  memset(szLine, 0, lineSize);
  sOK = gf_fgets(szLine, lineSize, txt_ina);
  if ( !sOK )
    return 0LL;
  if ( unicode_typea <= 1 )
  {
    j = 0;
    len = strlen(szLinea);
    for ( i = 0; ; ++i )
    {
      if ( i >= len )
      {
LABEL_19:
        szLineConv[j] = 0;
        strcpy(szLinea, szLineConv);
        return sOK;
      }
      if ( !unicode_typea && (szLinea[i] & 0x80) != 0 )
      {
        if ( (szLinea[i + 1] & 0xC0) == 128 )
        {
          if ( (szLinea[i] & 0xE0) == 192 )
          {
            szLineConv[j++] = szLinea[i++];
          }
          else if ( (szLinea[i] & 0xF0) == 224 )
          {
            szLineConv[j] = szLinea[i++];
            szLineConv[++j] = szLinea[i++];
            ++j;
          }
          else
          {
            if ( (szLinea[i] & 0xF8) != 240 )
            {
              ++i;
              continue;
            }
            szLineConv[j] = szLinea[i++];
            szLineConv[++j] = szLinea[i++];
            szLineConv[++j] = szLinea[i++];
            ++j;
          }
        }
        else
        {
          szLineConv[j++] = (szLinea[i] >> 6) & 3 | 0xC0;
          szLinea[i] &= ~0x40u;
        }
      }
      szLineConv[j++] = szLinea[i];
      if ( j >= 0x7FFuLL )
        goto LABEL_19;
    }
  }
  if ( unicode_typea == 2 )
  {
    for ( i = 0; szLinea[i] || szLinea[i + 1]; i += 2 )
    {
      c = szLinea[i + 1];
      szLinea[i + 1] = szLinea[i];
      szLinea[i] = c;
    }
  }
  sptr = (unsigned __int16 *)szLinea;
  i = gf_utf8_wcstombs(szLineConv, 0x800uLL, (const unsigned __int16 **)&sptr);
  if ( i == -1 )
    i = 0;
  szLineConv[i] = 0;
  strcpy(szLinea, szLineConv);
  if ( unicode_typea == 3 )
    gf_fgetc(txt_ina);
  return sOK;
}