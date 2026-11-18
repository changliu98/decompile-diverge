static inline unsigned int ring_size_to_bytes(unsigned int size) {
  unsigned int bytes;
  bytes = size * sizeof(unsigned int);
  return bytes;
}