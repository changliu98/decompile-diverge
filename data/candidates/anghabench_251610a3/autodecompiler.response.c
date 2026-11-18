__attribute__((used)) static char *get_level_str(int level)
{
 char *str;

 switch (level) {
 case LOG_LEVEL_QUIET:
  str = "quiet";
  break;
 case LOG_LEVEL_DEBUG:
  str = "debug";
  break;
 case LOG_LEVEL_VERBOSE:
  str = "verbose";
  break;
 case LOG_LEVEL_INFO:
  str = "info";
  break;
 case LOG_LEVEL_WARNING:
  str = "warning";
  break;
 case LOG_LEVEL_ERROR:
  str = "error";
  break;
 case LOG_LEVEL_FATAL:
  str = "fatal";
  break;
 case LOG_LEVEL_PANIC:
  str = "panic";
  break;
 default:
  str = "";
 }

 return str;
}