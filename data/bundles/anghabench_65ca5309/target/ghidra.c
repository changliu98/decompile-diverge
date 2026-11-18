char * ndcache_state2str(short ndp_state)

{
  char *ndp_state_str;
  short ndp_state_local;
  
  ndp_state_str = "UNKNOWN";
  switch(ndp_state) {
  case 0x80:
    ndp_state_str = "ND6_LLINFO_STALE";
    break;
  case 0x81:
    ndp_state_str = "ND6_LLINFO_REACHABLE";
    break;
  case 0x82:
    ndp_state_str = "ND6_LLINFO_PURGE";
    break;
  case 0x83:
    ndp_state_str = "ND6_LLINFO_PROBE";
    break;
  case 0x84:
    ndp_state_str = "ND6_LLINFO_NOSTATE";
    break;
  case 0x85:
    ndp_state_str = "ND6_LLINFO_INCOMPLETE";
    break;
  case 0x86:
    ndp_state_str = "ND6_LLINFO_DELAY";
  }
  return ndp_state_str;
}