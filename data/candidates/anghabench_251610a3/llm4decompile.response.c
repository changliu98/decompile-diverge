const char *get_level_str(int level)
{
    const char *level_str;

    switch (level) {
    case LOG_DEBUG:
        level_str = "debug";
        break;
    case LOG_INFO:
        level_str = "info";
        break;
    case LOG_ERROR:
        level_str = "error";
        break;
    case LOG_FATAL:
        level_str = "fatal";
        break;
    case LOG_PANIC:
        level_str = "panic";
        break;
    case LOG_WARNING:
        level_str = "warning";
        break;
    case LOG_VERBOSE:
        level_str = "verbose";
        break;
    case LOG_QUIET:
        level_str = "quiet";
        break;
    default:
        level_str = "";
    }

    return level_str;
}