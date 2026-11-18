const char *get_level_str(int level)
{
    switch (level)
    {
        case 128: return "warning";
        case 129: return "verbose";
        case 130: return "quiet";
        case 131: return "panic";
        case 132: return "info";
        case 133: return "fatal";
        case 134: return "error";
        case 135: return "debug";
        default:  return "";
    }
}