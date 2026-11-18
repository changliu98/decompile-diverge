int itostr(char *buf,int buflen,int x)

{
  char cVar1;
  char *pcVar2;
  char ch;
  char digit;
  char *beg;
  int cnt;
  int x_local;
  int buflen_local;
  char *buf_local;
  int local_c;
  
  if (buflen < 1) {
    local_c = 0;
  }
  else {
    x_local = x;
    buflen_local = buflen;
    buf_local = buf;
    if (x < 0) {
      *buf = '-';
      buf_local = buf + 1;
      buflen_local = buflen + -1;
      x_local = -x;
    }
    cnt = (int)(x < 0);
    if (buflen_local < 1) {
      local_c = cnt;
    }
    else {
      beg = buf_local;
      pcVar2 = buf_local;
      do {
        buf_local = pcVar2;
        *buf_local = (char)(x_local % 10) + '0';
        cnt = cnt + 1;
        buflen_local = buflen_local + -1;
        if (buflen_local < 1) {
          return cnt;
        }
        x_local = x_local / 10;
        pcVar2 = buf_local + 1;
      } while (0 < x_local);
      if (0 < buflen_local) {
        buf_local[1] = '\0';
      }
      for (; local_c = cnt, beg < buf_local; beg = beg + 1) {
        cVar1 = *beg;
        *beg = *buf_local;
        *buf_local = cVar1;
        buf_local = buf_local + -1;
      }
    }
  }
  return local_c;
}