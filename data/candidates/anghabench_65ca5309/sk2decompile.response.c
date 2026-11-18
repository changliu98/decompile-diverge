static const char *ndcache_state2str(short state) {
  const char *str = "UNKNOWN";
  switch (state) {
    case ND6_LLINFO_NOSTATE:
      str = "ND6_LLINFO_NOSTATE";
      break;
    case ND6_LLINFO_INCOMPLETE:
      str = "ND6_LLINFO_INCOMPLETE";
      break;
    case ND6_LLINFO_REACHABLE:
      str = "ND6_LLINFO_REACHABLE";
      break;
    case ND6_LLINFO_STALE:
      str = "ND6_LLINFO_STALE";
      break;
    case ND6_LLINFO_DELAY:
      str = "ND6_LLINFO_DELAY";
      break;
    case ND6_LLINFO_PROBE:
      str = "ND6_LLINFO_PROBE";
      break;
    case ND6_LLINFO_PURGE:
      str = "ND6_LLINFO_PURGE";
      break;
  }
  return str;
}