char_u * regtilde(char_u *source,int magic)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  char_u *__dest;
  int prevlen;
  int len;
  char_u *p;
  char_u *tmpsub;
  char_u *newsub;
  int magic_local;
  char_u *source_local;
  
  newsub = source;
  for (p = source; *p != '\0'; p = p + 1) {
    if (((*p == '~') && (magic != 0)) || ((*p == '\\' && ((p[1] == '~' && (magic == 0)))))) {
      if (reg_prev_sub == (char_u *)0x0) {
        if (magic == 0) {
          sVar3 = strlen((char *)(p + 2));
          memmove(p,p + 2,sVar3 + 1);
        }
        else {
          sVar3 = strlen((char *)(p + 1));
          memmove(p,p + 1,sVar3 + 1);
        }
      }
      else {
        sVar3 = strlen((char *)reg_prev_sub);
        iVar2 = (int)sVar3;
        sVar3 = strlen((char *)newsub);
        __dest = alloc(sVar3 + (long)iVar2);
        if (__dest != (char_u *)0x0) {
          iVar1 = (int)p - (int)newsub;
          memmove(__dest,newsub,(long)iVar1);
          memmove(__dest + iVar1,reg_prev_sub,(long)iVar2);
          if (magic == 0) {
            p = p + 1;
          }
          strcpy((char *)(__dest + (long)iVar2 + (long)iVar1),(char *)(p + 1));
          if (newsub != source) {
            vim_free(newsub);
          }
          p = __dest + (long)iVar2 + (long)iVar1;
          newsub = __dest;
        }
      }
      p = p + -1;
    }
    else {
      if ((*p == '\\') && (p[1] != '\0')) {
        p = p + 1;
      }
      if (has_mbyte != 0) {
        iVar2 = (*mb_ptr2len)(p);
        p = p + (iVar2 + -1);
      }
    }
  }
  vim_free(reg_prev_sub);
  reg_prev_sub = vim_strsave(newsub);
  return newsub;
}