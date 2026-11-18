static inline void copy_le16(unsigned char *dst, unsigned int val) {
  dst[0] = val;
  dst[1] = val >> 8;
}