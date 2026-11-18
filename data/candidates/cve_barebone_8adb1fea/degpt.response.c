void ga_concat_shorten_esc(garray_T *gap,char_u *str)

{
  int iVar1;
  int clen_00;
  int iVar2;
  bool bVar3;
  int same_len;
  char_u buf [65];
  int clen;
  int c;
  char_u *s;
  char_u *p;
  char_u *str_local;
  garray_T *gap_local;
  
  p = str;
  str_local = str;
  gap_local = gap;
  if (str == (char_u *)0x0) {
    ga_concat(gap,"NULL");
  }
  else {
    for (; *p != '\0'; p = p + 1) {
      same_len = 1;
      s = p;
      iVar1 = mb_ptr2char_adv(&s);
      clen_00 = (int)s - (int)p;
      while( true ) {
        bVar3 = false;
        if (*s != '\0') {
          iVar2 = (*mb_ptr2char)(s);
          bVar3 = iVar1 == iVar2;
        }
        if (!bVar3) break;
        same_len = same_len + 1;
        s = s + clen_00;
      }
      if (same_len < 0x15) {
        ga_concat_esc(gap_local,p,clen_00);
      }
      else {
        ga_concat(gap_local,"\\[");
        ga_concat_esc(gap_local,p,clen_00);
        ga_concat(gap_local,(char_u *)" occurs ");
        vim_snprintf((char *)buf,0x41,"%d",(ulong)(uint)same_len);
        ga_concat(gap_local,buf);
        ga_concat(gap_local,(char_u *)" times]");
        p = s + -1;
      }
    }
  }
  return;
}