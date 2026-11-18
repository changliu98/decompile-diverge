void trunc_string(char_u *s,char_u *buf,int room_in,int buflen)

{
  undefined2 uVar1;
  int iVar2;
  size_t sVar3;
  bool bVar4;
  int n;
  int i;
  int e;
  size_t len;
  size_t half;
  size_t room;
  int buflen_local;
  int room_in_local;
  char_u *buf_local;
  char_u *s_local;
  
  room = (size_t)(room_in + -3);
  len = 0;
  if (*s == '\0') {
    if (0 < buflen) {
      *buf = '\0';
    }
  }
  else {
    if (room_in < 3) {
      room = 0;
    }
    for (e = 0; len < room >> 1 && e < buflen; e = e + 1) {
      if (s[e] == '\0') {
        buf[e] = '\0';
        return;
      }
      n = ptr2cells(s + e);
      if (room >> 1 < len + (long)n) break;
      len = (long)n + len;
      buf[e] = s[e];
      if (has_mbyte != 0) {
        n = (*mb_ptr2len)(s + e);
        while ((n = n + -1, 0 < n && (e = e + 1, e != buflen))) {
          buf[e] = s[e];
        }
      }
    }
    i = e;
    if (enc_dbcs == 0) {
      if (enc_utf8 == 0) {
        sVar3 = strlen((char *)s);
        i = (int)sVar3;
        while( true ) {
          bVar4 = false;
          if (-1 < i + -1) {
            n = ptr2cells(s + (long)i + -1);
            bVar4 = len + (long)n <= room;
          }
          if (!bVar4) break;
          len = (long)n + len;
          i = i + -1;
        }
      }
      else {
        sVar3 = strlen((char *)s);
        i = (int)sVar3;
        half = (size_t)i;
        while( true ) {
          do {
            iVar2 = utf_head_off(s,s + (half - 1));
            half = (half - (long)iVar2) - 1;
            bVar4 = false;
            if (half != 0) {
              iVar2 = utf_ptr2char(s + half);
              iVar2 = utf_iscomposing(iVar2);
              bVar4 = iVar2 != 0;
            }
          } while (bVar4);
          iVar2 = ptr2cells(s + half);
          if ((room < len + (long)iVar2) || (half == 0)) break;
          len = (long)iVar2 + len;
          i = (int)half;
        }
      }
    }
    else {
      n = vim_strsize(s + e);
      while (room < len + (long)n) {
        iVar2 = ptr2cells(s + i);
        n = n - iVar2;
        iVar2 = (*mb_ptr2len)(s + i);
        i = iVar2 + i;
      }
    }
    uVar1 = DAT_00102004;
    if (e + 3 < i) {
      if (e + 3 < buflen) {
        (buf + e)[2] = DAT_00102006;
        *(undefined2 *)(buf + e) = uVar1;
        sVar3 = strlen((char *)(s + i));
        len = sVar3 + 1;
        if (((long)buflen - (long)e) - 3U <= len) {
          len = (size_t)((buflen - e) + -4);
        }
        memmove(buf + (long)e + 3,s + i,len);
        buf[(long)(e + 3) + len + -1] = '\0';
      }
      else {
        buf[e + -1] = '\0';
      }
    }
    else if (s != buf) {
      len = strlen((char *)s);
      if ((ulong)(long)buflen <= len) {
        len = (size_t)(buflen + -1);
      }
      sVar3 = (len - (long)e) + 1;
      if (sVar3 == 0) {
        buf[e + -1] = '\0';
      }
      else {
        memmove(buf + e,s + e,sVar3);
      }
    }
  }
  return;
}