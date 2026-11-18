const char *__cdecl ndcache_state2str(short ndp_state)
{
  const char *ndp_state_str; // [rsp+8h] [rbp-10h]

  ndp_state_str = "UNKNOWN";
  switch ( ndp_state )
  {
    case 128:
      ndp_state_str = "ND6_LLINFO_STALE";
      break;
    case 129:
      ndp_state_str = "ND6_LLINFO_REACHABLE";
      break;
    case 130:
      ndp_state_str = "ND6_LLINFO_PURGE";
      break;
    case 131:
      ndp_state_str = "ND6_LLINFO_PROBE";
      break;
    case 132:
      ndp_state_str = "ND6_LLINFO_NOSTATE";
      break;
    case 133:
      ndp_state_str = "ND6_LLINFO_INCOMPLETE";
      break;
    case 134:
      ndp_state_str = "ND6_LLINFO_DELAY";
      break;
    default:
      return ndp_state_str;
  }
  return ndp_state_str;
}