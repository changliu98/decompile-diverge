void str_cut(char *s, char *buf, int room, int buflen)
{
  int i; int j;
  unsigned long len;
  unsigned long room2;
  int n;
  int m;
  int is_mb;
  int is_mb2;
  int is_mb3;
  int is_mb4;
  char *p;
  room -= 3;
  len = 0;
  if (s[0] == '\0') {
    if (buflen > 0)
      buf[0] = '\0';
  }
  else {
    if (room < 3)
      room = 0;
    room2 = room / 2;
    for (i = 0;;) {
      is_mb = 0;
      if (len < room2)
        is_mb = i < buflen;
      if (!is_mb)
        break;
      if (s[i] == '\0') {
        buf[i] = '\0';
        return;
      }
      n = str_mblen(&s[i]);
      if (len + n > room2)
        break;
      len += n;
      buf[i] = s[i];
      if (has_mbyte) {
        n = mb_ptr2len(&s[i]);
        while (--n > 0) {
          if (++i == buflen)
            break;
          buf[i] = s[i];
        }
      }
    }
    j = i;
    if (enc_dbcs) {
      n = str_mblen2(&s[i]);
      while (len + n > room) {
        n = str_mblen(&s[j]);
        j += mb_ptr2len(&s[j]);
      }
    }
    else if (enc_utf8) {
      j = str_utf8len((char *)s);
      for (p = (char *)s + j;;) {
        j = p - (char *)s;
        p = (char *)s + (str_utf8len2((char *)s, p - (char *)s) - 1);
        is_mb2 = 0;
        if (p - (char *)s - 1 > 0)
          is_mb2 = str_utf8iscont(str_utf8len2((char *)s, p - (char *)s)) != 0;
        while (is_mb2) {
          p = (char *)s + (str_utf8len2((char *)s, p - (char *)s) - 1);
          is_mb2 = 0;
          if (p - (char *)s - 1 > 0)
            is_mb2 = str_utf8iscont(str_utf8len2((char *)s, p - (char *)s)) != 0;
        }
        n = str_mblen(&s[p - (char *)s]);
        if (len + n > room || p - (char *)s == 0)
          break;
        len += n;
      }
    }
    else {
      for (j = str_utf8len((char *)s); j > 0;) {
        is_mb3 = 0;
        if (j - 1 > 0) {
          n = str_mblen(&s[j - 1]);
          is_mb3 = len + n <= room;
        }
        if (!is_mb3)
          break;
        len += n;
        --j;
      }
    }
    if (j > i + 3) {
      if (i + 3 < buflen) {
        buf[i + 2] = '.';
        buf[i + 1] = 'v';
        buf[i + 0] = '8';
        len += str_utf8len((char *)&s[j]) + 1;
        if (len > buflen - i - 3)
          len = buflen - i - 4;
        str_utf8cpy(&buf[i + 3], (char *)&s[j], len);
        buf[i + len + 3] = '\0';
      }
      else
        buf[i - 1] = '\0';
    }
    else if (s != buf) {
      len = str_utf8len((char *)s);
      if (len >= buflen)
        len = buflen - 1;
      len = len - i + 1;
      if (len > 0)
        str_utf8cpy(&buf[i], (char *)&s[i], len);
      else
        buf[i - 1] = '\0';
    }
  }
}