static inline unsigned int match_len2state(unsigned int len)
{
  if (len < MATCH_LEN_MIN + DIST_STATES)
    return len - MATCH_LEN_MIN;
  else
    return DIST_STATES - 1;
}