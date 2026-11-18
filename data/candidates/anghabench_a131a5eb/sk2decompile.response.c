static inline unsigned lzma_get_dist_state(unsigned dist) {
  if (dist < DIST_SLOTS + DIST_MODEL_END)
    return dist - DIST_SLOTS;
  else
    return DIST_MODEL_END - 1;
}