void __cdecl trunc_string(char_u *s, char_u *buf, int room_in, int buflen)
{
  int n;
  int i;
  int e;
  size_t len;
  size_t half;
  size_t room;

  if (!*s)
  {
    if (buflen > 0)
      *buf = 0;
    return;
  }

  room = room_in - 3;
  if (room_in < 3)
    room = 0;

  half = room >> 1;
  len = 0;

  // 1. Copy the first half of the string into buf
  for (e = 0; ; ++e)
  {
    if (len >= half || e >= buflen)
      break;

    if (!s[e])
    {
      buf[e] = 0;
      return;
    }

    n = ptr2cells(&s[e]);
    if (n + len > half)
      break;

    len += n;
    buf[e] = s[e];

    if (has_mbyte)
    {
      n = mb_ptr2len(&s[e]);
      while (--n > 0)
      {
        if (++e == buflen)
          break;
        buf[e] = s[e];
      }
    }
  }

  // 2. Find the starting index 'i' of the second half of the string
  if (enc_dbcs)
  {
    int na = vim_strsize(&s[e]);
    i = e;
    while (na + len > room)
    {
      na -= ptr2cells(&s[i]);
      i += mb_ptr2len(&s[i]);
    }
  }
  else if (enc_utf8)
  {
    size_t halfa;
    i = strlen((const char *)s);
    halfa = i;

    for (;; i = halfa)
    {
      // Skip over composing characters
      do
      {
        size_t prev_halfa = halfa;
        int offset = utf_head_off(s, &s[halfa - 1]);
        halfa = halfa - offset - 1;

        bool is_composing = false;
        if (prev_halfa - offset != 1)
        {
          int c = utf_ptr2char(&s[halfa]);
          is_composing = (utf_iscomposing(c) != 0);
        }
      } while (is_composing);

      nb = ptr2cells(&s[halfa]);
      if (nb + len > room || !halfa)
        break;

      len += nb;
    }
  }
  else
  {
    i = strlen((const char *)s);
    for (; i - 1 >= 0; --i)
    {
      n = ptr2cells(&s[i - 1]);
      if (n + len > room)
        break;
      len += n;
    }
  }

  // 3. Construct the final truncated string
  if (i > e + 3)
  {
    if (e + 3 >= buflen)
    {
      buf[e - 1] = 0;
    }
    else
    {
      char_u *p = &buf[e];
      p[2] = '.';
      *(_WORD *)p = ELLIPSIS_STR; // Writes ".." at p[0] and p[1]

      size_t lenc = strlen((const char *)&s[i]) + 1;
      if (lenc >= buflen - (__int64)e - 3)
        lenc = buflen - e - 4;

      memmove(&buf[e + 3], &s[i], lenc);
      buf[lenc + 2 + e] = 0;
    }
  }
  else if (s != buf)
  {
    size_t lena = strlen((const char *)s);
    if (lena >= buflen)
      lena = buflen - 1;

    __int64 lenb = lena - e + 1;
    if (lenb)
      memmove(&buf[e], &s[e], lenb);
    else
      buf[e - 1] = 0;
  }
}