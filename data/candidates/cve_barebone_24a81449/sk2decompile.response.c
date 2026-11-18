int archive_string_append_from_wcs(struct archive_string *as, const wchar_t *p,
                                   size_t len) {
  int ret = 0;
  char *p1, *p2, *p3;
  int r;
  mbstate_t mbs;
  memset(&mbs, 0, sizeof(mbs));
  if (archive_string_ensure(as, as->length + len + 1) == NULL) return (-1);
  p1 = as->s + as->length;
  p2 = as->s + as->buffer_length;
  p3 = p2 - (MB_CUR_MAX() + 1);
  while (*p != L'\0' && len > 0) {
    if (p1 >= p3) {
      as->length = p1 - as->s;
      as->s[as->length] = '\0';
      if (archive_string_ensure(as, as->length + len * 2 + 1) == NULL)
        return (-1);
      p1 = as->s + as->length;
      p2 = as->s + as->buffer_length;
      p3 = p2 - (MB_CUR_MAX() + 1);
    }
    r = wcrtomb(p1, *p++, &mbs);
    if (r == -1) {
      if (errno != EILSEQ) {
        ret = -1;
        break;
      }
      *p1++ = '?';
      ret = -1;
    } else
      p1 += r;
    len--;
  }
  as->length = p1 - as->s;
  as->s[as->length] = '\0';
  return (ret);
}