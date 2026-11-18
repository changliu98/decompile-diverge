char *nd6_llinfo_state2str(int state)
{
    char *str = "UNKNOWN";
    switch (state) {
    case ND_STALE:
        str = "ND6_LLINFO_STALE";
        break;
    case ND_REACHABLE:
        str = "ND6_LLINFO_REACHABLE";
        break;
    case ND_INCOMPLETE:
        str = "ND6_LLINFO_INCOMPLETE";
        break;
    case ND_DELAY:
        str = "ND6_LLINFO_DELAY";
        break;
    case ND_PROBE:
        str = "ND6_LLINFO_PROBE";
        break;
    case ND_NOSTATE:
        str = "ND6_LLINFO_NOSTATE";
        break;
    case ND_PERMANENT:
        str = "ND6_LLINFO_PURGE";
        break;
    case ND_NONE:
        str = "ND6_LLINFO_NONE";
        break;
    default:
        break;
    }
    return str;
}