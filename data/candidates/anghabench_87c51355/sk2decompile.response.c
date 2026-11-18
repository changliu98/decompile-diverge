static inline int spc_used(unsigned wp, unsigned rp, unsigned size) {
  int used = wp - rp;
  if (used >= 0)
    return used;
  else
    return used + size;
}