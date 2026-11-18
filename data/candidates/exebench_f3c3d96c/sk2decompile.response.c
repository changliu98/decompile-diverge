static void nist_increment_block(unsigned int *block) {
  unsigned int tmp;
  int i;
  for (i = 3; i >= 0; i--) {
    tmp = ntohl(block[i]) + 1;
    block[i] = htonl(tmp);
    if (tmp) break;
  }
}