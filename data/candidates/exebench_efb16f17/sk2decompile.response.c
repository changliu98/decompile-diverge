unsigned int ether_hash(unsigned char *addr) {
  int i;
  unsigned int hash = 0;
  for (i = 0; i < 6; i++) {
    hash = (hash << 6) + (hash << 16) + addr[i] - hash;
  }
  return hash;
}