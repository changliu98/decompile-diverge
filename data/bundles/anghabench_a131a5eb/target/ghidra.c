uint32_t lzma_get_dist_state(uint32_t len)

{
  undefined4 local_18;
  uint32_t len_local;
  
  if ((long)(ulong)len < DIST_STATES + MATCH_LEN_MIN) {
    local_18 = len - (int)MATCH_LEN_MIN;
  }
  else {
    local_18 = DIST_STATES - 1;
  }
  return local_18;
}