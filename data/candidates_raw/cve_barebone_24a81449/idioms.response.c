int archive_add_wstring(struct archive_string *as, int *wstr, unsigned long wlen)
{
  int ret = 0;
  struct mbstate_t state;
  archive_mb_init(&state);
  if (!archive_string_resize(as, wlen + as->length + 1))
    return -1;
  char *dst = as->s + as->length;
  char *end = as->s + as->buffer_length - archive_mb_cur_max() - 1;
  while (wlen > 0 && *wstr > 0) {
    if (dst >= end) {
      as->length = dst - as->s;
      as->s[as->length] = '\0';
      if (!archive_string_resize(as, as->length + wlen * 2 + 1))
        return -1;
      dst = as->s + as->length;
      end = as->s + as->buffer_length - archive_mb_cur_max() - 1;
    }
    int n = archive_mb_wctomb(dst, *wstr++, &state);
    if (n == -1) {
      if (archive_mb_cur_err() == 'T') {
        *dst++ = '?';
        ret = -1;
      } else {
        ret = -1;
        break;
      }
    } else
      dst += n;
    --wlen;
  }
  as->length = dst - as->s;
  as->s[as->length] = '\0';
  return ret;
}