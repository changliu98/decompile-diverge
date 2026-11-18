int lzma_get_dist_state(int a)
{
  UInt32 slot;
  if (a < MATCH_LEN_MIN + DIST_STATES)
    slot = a - MATCH_LEN_MIN;
  else
    slot = DIST_STATES - 1;
  return slot;
}