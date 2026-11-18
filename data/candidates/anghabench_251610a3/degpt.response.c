/*
 * get_level_str - Converts a numeric log level to its string representation.
 *
 * @level: The numeric log level constant.
 *
 * Returns: A pointer to a static string corresponding to the log level,
 *          or an empty string if the level is unrecognized.
 */
char * get_level_str(int log_level)
{
  switch(log_level) {
  case 0x80: return "warning";
  case 0x81: return "verbose";
  case 0x82: return "quiet";
  case 0x83: return "panic";
  case 0x84: return "info";
  case 0x85: return "fatal";
  case 0x86: return "error";
  case 0x87: return "debug";
  default: return "";
  }
}