static int
wcscpy(struct archive_string *as, wchar_t *wcs, size_t len)
{
 mbstate_t mbs;
 char *p, *pe;
 int ret = 0;

 memset(&mbs, 0, sizeof(mbs));
 if (!archive_string_ensure(as, as->length + len + 1))
  return (-1);
 p = as->s + as->length;
 pe = as->s + as->size + as->length - ___ctype_get_mb_cur_max() - 1;
 for (;;) {
  if ((int)len <= 0 && *wcs == L'\0')
   break;
  if (p >= pe) {
   as->length = p - as->s;
   as->s[as->length] = '\0';
   if (!archive_string_ensure(as, as->length + len * 2 + 1))
    return (-1);
   p = as->s + as->length;
   pe = as->s + as->size + as->length - ___ctype_get_mb_cur_max() - 1;
  }
  {
   int l = wcrtomb(p, *wcs++, &mbs);
   if (l == -1) {
    if (*___errno_location() == 84) {
     *p++ = '?';
     ret = -1;
    } else
     ret = -1;
   } else
    p += l;
  }
  len--;
 }
 as->length = p - as->s;
 as->s[as->length] = '\0';
 return (ret);
}