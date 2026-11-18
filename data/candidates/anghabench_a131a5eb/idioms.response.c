static inline unsigned int lzma_get_dist_state(unsigned int len)
{
  if (len < MATCH_LEN_MIN + DIST_STATES)
    return len - MATCH_LEN_MIN;
  else
    return DIST_STATES - 1;
}