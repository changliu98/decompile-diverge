static inline void bnode_link_set_ref(unsigned int *link, unsigned int ref) {
  unsigned int l = *link;
  l &= 1;
  l |= (ref + 1) << 1;
  *link = l;
}