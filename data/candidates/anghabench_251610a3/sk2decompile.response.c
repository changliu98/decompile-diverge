static const char *get_level_str(log_level_t level) {
  const char *str;
  switch (level) {
    case LOG_PANIC:
      str = "panic";
      break;
    case LOG_FATAL:
      str = "fatal";
      break;
    case LOG_ERROR:
      str = "error";
      break;
    case LOG_WARNING:
      str = "warning";
      break;
    case LOG_INFO:
      str = "info";
      break;
    case LOG_VERBOSE:
      str = "verbose";
      break;
    case LOG_DEBUG:
      str = "debug";
      break;
    case LOG_QUIET:
      str = "quiet";
      break;
    default:
      str = "";
      break;
  }
  return str;
}