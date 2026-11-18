char *ndcache_state2str(short state)
{
 char *states[] = {
  "UNKNOWN",
  "ND6_LLINFO_PURGE",
  "ND6_LLINFO_NOSTATE",
  "ND6_LLINFO_INCOMPLETE",
  "ND6_LLINFO_REACHABLE",
  "ND6_LLINFO_STALE",
  "ND6_LLINFO_DELAY",
  "ND6_LLINFO_PROBE"
 };
 int idx;

 switch(state) {
  case ND6_LLINFO_PURGE: idx = 1; break;
  case ND6_LLINFO_NOSTATE: idx = 2; break;
  case ND6_LLINFO_INCOMPLETE: idx = 3; break;
  case ND6_LLINFO_REACHABLE: idx = 4; break;
  case ND6_LLINFO_STALE: idx = 5; break;
  case ND6_LLINFO_DELAY: idx = 6; break;
  case ND6_LLINFO_PROBE: idx = 7; break;
  default: idx = 0;
 }
 return states[idx];
}