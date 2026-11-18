int memcached_udp_set_cookie(unsigned char *buffer, size_t nkey,
                             unsigned long cookie) {
  if (nkey >= 2) {
    buffer[0] = (unsigned char)(cookie >> 8);
    buffer[1] = (unsigned char)(cookie & 0xff);
  }
  return 0;
}