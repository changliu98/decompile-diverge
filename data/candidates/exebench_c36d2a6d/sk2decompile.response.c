static inline int epindex_to_epnum(int epindex, int *is_in) {
  int is_in_ep;
  is_in_ep = epindex % 2;
  if (is_in) *is_in = is_in_ep;
  return (epindex + is_in_ep) / 2;
}