uint32_t __cdecl lzma_get_dist_state(uint32_t len)
{
  if (len >= MATCH_LEN_MIN + DIST_STATES)
    return DIST_STATES - 1;
  return len - MATCH_LEN_MIN;
}