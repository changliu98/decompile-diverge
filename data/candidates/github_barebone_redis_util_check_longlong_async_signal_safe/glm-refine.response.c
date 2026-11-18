const char *__cdecl check_longlong_async_signal_safe(const char *fmt, int32_t *have_longlong)
{
  const char *fmta = fmt;

  *have_longlong = 0;
  
  // Check if the first character is 'l' (ASCII 108)
  if (*fmt == 'l')
  {
    fmta = fmt + 1;
    
    // Check if the second character is also 'l' (e.g., "ll" for long long)
    if (fmt[1] == 'l')
    {
      fmta = fmt + 2;
    }
    
    *have_longlong = 1;
  }
  
  return fmta;
}