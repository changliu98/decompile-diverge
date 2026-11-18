static const char *check_longlong_async_signal_safe(const char *fmt, int32_t *have_longlong) {
    *have_longlong = 0;
    if (*fmt == 'l') {
        fmt++;
        if (*fmt != 'l') {
            *have_longlong = (sizeof(long) == sizeof(int64_t));
        } else {
            fmt++;
            *have_longlong = 1;
        }
    }
    return fmt;
}