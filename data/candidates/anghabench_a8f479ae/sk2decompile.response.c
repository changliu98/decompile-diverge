static unsigned int ice_txd_use_count(unsigned int size) {
  unsigned int use_count;
  use_count = (size * 85) >> 20;
  use_count++;
  return use_count;
}