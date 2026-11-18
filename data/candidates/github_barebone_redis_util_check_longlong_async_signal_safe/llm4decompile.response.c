const char* check_longlong_async_signal_safe(const char* fmt, int32_t* have_longlong) {
  *have_longlong = 0;
  if (*fmt == 'l') {
    ++fmt;
    if (*fmt == 'l') {
      ++fmt;
    }
    *have_longlong = 1;
  }
  return fmt;
}