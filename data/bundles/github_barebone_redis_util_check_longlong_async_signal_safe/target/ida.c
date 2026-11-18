const char *__cdecl check_longlong_async_signal_safe(const char *fmt, int32_t *have_longlong)
{
  const char *fmta; // [rsp+8h] [rbp-8h]

  fmta = fmt;
  *have_longlong = 0;
  if ( *fmt == 108 )
  {
    fmta = fmt + 1;
    if ( fmt[1] == 108 )
      fmta = fmt + 2;
    *have_longlong = 1;
  }
  return fmta;
}