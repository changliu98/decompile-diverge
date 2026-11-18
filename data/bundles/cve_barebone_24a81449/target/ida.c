int __cdecl archive_string_append_from_wcs(archive_string *as, const wchar_t *w, size_t len)
{
  wchar_t *v3; // rax
  char *v4; // rax
  char *v6; // [rsp+8h] [rbp-58h]
  bool v7; // [rsp+17h] [rbp-49h]
  char *v8; // [rsp+18h] [rbp-48h]
  mbstate_t shift_state; // [rsp+20h] [rbp-40h] BYREF
  char *end; // [rsp+28h] [rbp-38h]
  char *p; // [rsp+30h] [rbp-30h]
  int ret_val; // [rsp+38h] [rbp-28h]
  int n; // [rsp+3Ch] [rbp-24h]
  size_t lena; // [rsp+40h] [rbp-20h]
  const wchar_t *wa; // [rsp+48h] [rbp-18h]
  archive_string *asa; // [rsp+50h] [rbp-10h]

  asa = as;
  wa = w;
  lena = len;
  ret_val = 0;
  memset(&shift_state, 0, sizeof(shift_state));
  if ( !archive_string_ensure(asa, lena + asa->length + 1) )
    return -1;
  p = &asa->s[asa->length];
  v8 = &asa->s[asa->buffer_length];
  end = &v8[-__ctype_get_mb_cur_max() - 1];
  while ( 1 )
  {
    v7 = 0;
    if ( *wa )
      v7 = lena != 0;
    if ( !v7 )
      break;
    if ( p >= end )
    {
      asa->length = p - asa->s;
      asa->s[asa->length] = 0;
      if ( !archive_string_ensure(asa, 2 * lena + asa->length + 1) )
        return -1;
      p = &asa->s[asa->length];
      v6 = &asa->s[asa->buffer_length];
      end = &v6[-__ctype_get_mb_cur_max() - 1];
    }
    v3 = (wchar_t *)wa++;
    n = wcrtomb(p, *v3, &shift_state);
    if ( n == -1 )
    {
      if ( *__errno_location() != 84 )
      {
        ret_val = -1;
        break;
      }
      v4 = p++;
      *v4 = 63;
      ret_val = -1;
    }
    else
    {
      p += n;
    }
    --lena;
  }
  asa->length = p - asa->s;
  asa->s[asa->length] = 0;
  return ret_val;
}