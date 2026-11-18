static void trunc_string(char_u *str, char_u *buf, int max, int buf_len) {
  int len;
  int i;
  int j;
  int k;
  int half;
  unsigned int used;
  unsigned int max_used;
  max_used = max - 3;
  used = 0;
  if (str[0] == 0) {
    if (buf_len > 0) buf[0] = 0;
    return;
  }
  if (max_used < 0) max_used = 0;
  half = max_used / 2;
  for (i = 0; used < half && i < buf_len; i++) {
    if (str[i] == 0) {
      buf[i] = 0;
      return;
    }
    len = ptr2cells(str + i);
    if (used + len > half) break;
    used += len;
    buf[i] = str[i];
    if (mb_is_on) {
      len = mb_ptr2len(str + i);
      while (--len > 0) {
        i++;
        if (i == buf_len) break;
        buf[i] = str[i];
      }
    }
  }
  k = i;
  if (mb_is_on_2) {
    len = vim_strsize(str + k);
    while (used + len > max_used) {
      len -= ptr2cells(str + k);
      k += mb_ptr2len(str + k);
    }
  } else if (mb_is_on_3) {
    k = strlen((char *)str);
    for (;;) {
      len = k;
      len -= utf_head_off(str, str + len - 1);
      len--;
      if (len == 0 || !utf_iscomposing(utf_ptr2char(str + len))) break;
      k = len;
    }
    len = ptr2cells(str + k);
    if (used + len > max_used || k == 0) goto ellipsis;
    used += len;
  } else {
    k = strlen((char *)str);
    for (;;) {
      len = k - 1;
      if (len < 0) break;
      len = ptr2cells(str + len);
      if (used + len > max_used) break;
      used += len;
      k--;
    }
  }
ellipsis:
  if (k <= i + 3) {
    if (str != buf) {
      len = strlen((char *)str);
      if (len >= buf_len) len = buf_len - 1;
      len -= i;
      if (len == 0)
        buf[i - 1] = 0;
      else
        memmove(buf + i, str + i, len);
    }
  } else {
    if (i + 3 < buf_len) {
      buf[i] = 'v';
      buf[i + 1] = '.';
      buf[i + 2] = '.';
      len = strlen((char *)str + k) + 1;
      if (len >= buf_len - i - 3) len = buf_len - i - 4;
      memmove(buf + i + 3, str + k, len);
      buf[i + 3 + len] = 0;
    } else
      buf[i - 1] = 0;
  }
}