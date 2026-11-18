char * ndcache_state2str(short ndp_state)
{
    switch(ndp_state) {
    case 0x80:
        return "ND6_LLINFO_STALE";
    case 0x81:
        return "ND6_LLINFO_REACHABLE";
    case 0x82:
        return "ND6_LLINFO_PURGE";
    case 0x83:
        return "ND6_LLINFO_PROBE";
    case 0x84:
        return "ND6_LLINFO_NOSTATE";
    case 0x85:
        return "ND6_LLINFO_INCOMPLETE";
    case 0x86:
        return "ND6_LLINFO_DELAY";
    default:
        return "UNKNOWN";
    }
}