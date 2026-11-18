void msg_puts_printf(char_u *str,int maxlen)

{
  int iVar1;
  char *str_00;
  size_t sVar2;
  bool bVar3;
  char_u *tofree;
  int n;
  char_u *p;
  char_u *buf;
  char_u *s;
  int maxlen_local;
  char_u *str_local;
  
  p = str;
  s = str;
  while( true ) {
    if ((maxlen < 0) || (bVar3 = false, (int)s - (int)str < maxlen)) {
      bVar3 = *s != '\0';
    }
    if (!bVar3) break;
    if (((silent_mode == 0) || (p_verbose != 0)) && (*s == '\n')) {
      iVar1 = (int)s - (int)p;
      str_00 = alloc((long)(iVar1 + 3));
      if (str_00 != (char *)0x0) {
        memcpy(str_00,p,(long)iVar1);
        n = iVar1;
        if (info_message == 0) {
          n = iVar1 + 1;
          str_00[iVar1] = '\r';
        }
        str_00[n] = '\n';
        str_00[n + 1] = '\0';
        if (info_message == 0) {
          mch_errmsg(str_00);
        }
        else {
          mch_msg(str_00);
        }
        vim_free(str_00);
      }
      p = s + 1;
    }
    if ((*s == '\r') || (*s == '\n')) {
      msg_col = 0;
    }
    else {
      msg_col = msg_col + 1;
    }
    s = s + 1;
  }
  if ((*p != '\0') && ((silent_mode == 0 || (p_verbose != 0)))) {
    tofree = (char_u *)0x0;
    if ((0 < maxlen) && (sVar2 = strlen((char *)p), (ulong)(long)maxlen < sVar2)) {
      tofree = vim_strnsave(p,(long)maxlen);
      p = tofree;
    }
    if (p != (char_u *)0x0) {
      if (info_message == 0) {
        mch_errmsg((char *)p);
      }
      else {
        mch_msg((char *)p);
      }
      vim_free(tofree);
    }
  }
  msg_didout = 1;
  return;
}