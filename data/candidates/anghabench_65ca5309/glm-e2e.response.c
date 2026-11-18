const char *ndcache_state2str(int16_t state) {
    const char *str = "unknown";
    int32_t norm = state - 0x80;

    switch (norm) {
        case 0:
            str = "INCOMPLETE";
            break;
        case 1:
            str = "REACHABLE";
            break;
        case 2:
            str = "STALE";
            break;
        case 3:
            str = "DELAY";
            break;
        case 4:
            str = "PROBE";
            break;
        case 5:
            str = "FAILED";
            break;
        case 6:
            str = "NOARP";
            break;
        default:
            // Falls through to return "unknown"
            break;
    }

    return str;
}