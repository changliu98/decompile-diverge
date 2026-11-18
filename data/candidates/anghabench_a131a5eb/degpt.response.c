uint32_t calculate_distance_state(uint32_t match_length)
{
  // Calculate the distance state based on the match length.
  // If the length is less than the sum of DIST_STATES and MATCH_LEN_MIN,
  // return the offset from MATCH_LEN_MIN.
  if (match_length < DIST_STATES + MATCH_LEN_MIN) {
    return match_length - MATCH_LEN_MIN;
  }
  // Otherwise, return the maximum distance state.
  return DIST_STATES - 1;
}