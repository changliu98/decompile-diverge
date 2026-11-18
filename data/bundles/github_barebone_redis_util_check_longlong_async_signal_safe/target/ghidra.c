char * check_longlong_async_signal_safe(char *fmt,int32_t *have_longlong)

{
  int32_t *have_longlong_local;
  char *fmt_local;
  
  *have_longlong = 0;
  fmt_local = fmt;
  if (*fmt == 'l') {
    fmt_local = fmt + 1;
    if (*fmt_local == 'l') {
      fmt_local = fmt + 2;
      *have_longlong = 1;
    }
    else {
      *have_longlong = 1;
    }
  }
  return fmt_local;
}