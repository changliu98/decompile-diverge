char *check_longlong_async_signal_safe(char *str, int *have_longlong)
{
  *have_longlong = 0;
  if ( *str == 'l' )
  {
    str++;
    if ( *str == 'l' )
      str++;
    *have_longlong = 1;
  }
  return str;
}