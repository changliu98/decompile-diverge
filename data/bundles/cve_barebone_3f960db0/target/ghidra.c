char * gf_text_get_utf8_line(char *szLine,u32 lineSize,FILE *txt_in,s32 unicode_type)

{
  char cVar1;
  size_t sVar2;
  char c;
  unsigned_short *sptr;
  char szLineConv [2048];
  char *sOK;
  u32 len;
  u32 j;
  u32 i;
  s32 unicode_type_local;
  FILE *txt_in_local;
  u32 lineSize_local;
  char *szLine_local;
  char *local_10;
  
  memset(szLine,0,(ulong)lineSize);
  local_10 = gf_fgets(szLine,(ulong)lineSize,txt_in);
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else if (unicode_type < 2) {
    j = 0;
    sVar2 = strlen(szLine);
    for (i = 0; i < (uint)sVar2; i = i + 1) {
      if ((unicode_type == 0) && (((int)szLine[i] & 0x80U) != 0)) {
        if (((int)szLine[i + 1] & 0xc0U) != 0x80) {
          szLineConv[j] = szLine[i] >> 6 & 3U | 0xc0;
          j = j + 1;
          szLine[i] = szLine[i] & 0xbf;
          goto LAB_00101508;
        }
        if (((int)szLine[i] & 0xe0U) == 0xc0) {
          szLineConv[j] = szLine[i];
          i = i + 1;
          j = j + 1;
          goto LAB_00101508;
        }
        if (((int)szLine[i] & 0xf0U) == 0xe0) {
          szLineConv[j] = szLine[i];
          szLineConv[j + 1] = szLine[i + 1];
          i = i + 2;
          j = j + 2;
          goto LAB_00101508;
        }
        if (((int)szLine[i] & 0xf8U) == 0xf0) {
          szLineConv[j] = szLine[i];
          szLineConv[j + 1] = szLine[i + 1];
          szLineConv[j + 2] = szLine[i + 2];
          i = i + 3;
          j = j + 3;
          goto LAB_00101508;
        }
        i = i + 1;
      }
      else {
LAB_00101508:
        szLineConv[j] = szLine[i];
        j = j + 1;
        if (0x7fe < j) break;
      }
    }
    szLineConv[j] = '\0';
    strcpy(szLine,szLineConv);
  }
  else {
    if (unicode_type == 2) {
      i = 0;
      while ((szLine[i] != '\0' || (szLine[i + 1] != '\0'))) {
        cVar1 = szLine[i + 1];
        szLine[i + 1] = szLine[i];
        szLine[i] = cVar1;
        i = i + 2;
      }
    }
    sptr = (unsigned_short *)szLine;
    i = gf_utf8_wcstombs(szLineConv,0x800,&sptr);
    if (i == 0xffffffff) {
      i = 0;
    }
    szLineConv[i] = '\0';
    strcpy(szLine,szLineConv);
    if (unicode_type == 3) {
      gf_fgetc(txt_in);
    }
  }
  return local_10;
}