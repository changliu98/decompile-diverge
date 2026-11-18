char *url_canonize2(char *dest, char *src, size_t n, int escape_char,
                 int disallow, int disallow_add, int disallow_always) {
  size_t i = 0;
  unsigned char c, d, e, f, g, h, j, k, l, m, o, p, q, r, s, t, u, v, w, x, y, z;

  if (dest == src) {
    while ((c = src[i]) && i < n) {
      if (c == '%' || c == escape_char) {
        if (c == '%') {
          if (!src[i + 1] || !src[i + 2]) {
            *dest = '\0';
            return NULL;
          }
          d = src[i + 1];
          e = src[i + 2];
          if (((((d >= '0' && d <= '9') || (d >= 'A' && d <= 'F') || (d >= 'a' && d <= 'f')) && ((e >= '0' && e <= '9') || (e >= 'A' && e <= 'F') || (e >= 'a' && e <= 'f'))) ? 1 : 0)) {
            c = (((((((d) >= 'a') ? (d) - 'a' + 'A' : (d)) - ((((d) >= 'A') ? (d) - 'A' + '0' : (d)) - '0') * 10) << 4) | ((((((e) >= 'a') ? (e) - 'a' + 'A' : (e)) - ((((e) >= 'A') ? (e) - 'A' + '0' : (e)) - '0') * 10))) & 0xFF);
            if ((((c) > 32 && (c) < 128) ? ((disallow_always & (1 << (127 - (c)))) ? 1 : 0) : (((c) < 33) ? ((disallow & (1 << (63 - (c)))) ? 1 : 0) : ((disallow_add & (1 << (95 - (c)))) ? 1 : 0))))
              goto escape;
            *dest++ = c;
            i += 2;
          } else {
            *dest = '\0';
            return NULL;
          }
        } else {
          *dest++ = c;
        }
      } else {
        *dest++ = c;
      }
      ++dest;
      ++i;
    }
    *dest = '\0';
    return dest;
  }

  while ((c = src[i]) && i < n) {
    if (c == '%' || c == escape_char) {
      if (c == '%') {
        if (!src[i + 1] || !src[i + 2]) {
          *dest = '\0';
          return NULL;
        }
        d = src[i + 1];
        e = src[i + 2];
        if (((((d >= '0' && d <= '9') || (d >= 'A' && d <= 'F') || (d >= 'a' && d <= 'f')) && ((e >= '0' && e <= '9') || (e >= 'A' && e <= 'F') || (e >= 'a' && e <= 'f'))) ? 1 : 0)) {
          c = (((((((d) >= 'a') ? (d) - 'a' + 'A' : (d)) - ((((d) >= 'A') ? (d) - 'A' + '0' : (d)) - '0') * 10) << 4) | ((((((e) >= 'a') ? (e) - 'a' + 'A' : (e)) - ((((e) >= 'A') ? (e) - 'A' + '0' : (e)) - '0') * 10))) & 0xFF);
          if ((((c) > 32 && (c) < 128) ? ((disallow_always & (1 << (127 - (c)))) ? 1 : 0) : (((c) < 33) ? ((disallow & (1 << (63 - (c)))) ? 1 : 0) : ((disallow_add & (1 << (95 - (c)))) ? 1 : 0)))) {
            goto escape;
          }
          *dest++ = c;
          i += 2;
        } else {
          *dest = '\0';
          return NULL;
        }
      } else {
        *dest++ = c;
      }
    } else {
      *dest++ = c;
    }
    ++dest;
    ++i;
  }
  *dest = '\0';
  return dest;
escape:
  if (c == '%' || c == escape_char) {
    if (c == '%') {
      if (!src[i + 1] || !src[i + 2]) {
        *dest = '\0';
        return NULL;
      }
      d = src[i + 1];
      e = src[i + 2];
      if (((((d >= '0' && d <= '9') || (d >= 'A' && d <= 'F') || (d >= 'a' && d <= 'f')) && ((e >= '0' && e <= '9') || (e >= 'A' && e <= 'F') || (e >= 'a' && e <= 'f'))) ? 1 : 0)) {
        c = (((((((d) >= 'a') ? (d) - 'a' + 'A' : (d)) - ((((d) >= 'A') ? (d) - 'A' + '0' : (d)) - '0') * 10) << 4) | ((((((e) >= 'a') ? (e) - 'a' + 'A' : (e)) - ((((e) >= 'A') ? (e) - 'A' + '0' : (e)) - '0') * 10))) & 0xFF);
        if (c == '%')
          *dest++ = c;
        else {
          if (d >= 'a')
            d -= ('a' - 'A');
          if (e >= 'a')
            e -= ('a' - 'A');
          *dest++ = '%';
          *dest++ = d;
          *dest++ = e;
          i += 2;
        }
      } else {
        *dest = '\0';
        return NULL;
      }
    } else {
      *dest++ = escape_char;
      *dest++ = c;
    }
  } else {
    *dest++ = escape_char;
    *dest++ = c;
  }
  ++dest;
  ++i;
  while ((c = src[i]) && i < n) {
    *dest++ = c;
    ++dest;
    ++i;
  }
  *dest = '\0';
  return dest;
}