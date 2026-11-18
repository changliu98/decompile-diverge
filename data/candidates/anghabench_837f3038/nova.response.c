static int memcached_udp_set_cookie(char *out, size_t out_size, unsigned long long in) {
  int bytes_written = 0;

  if (out_size < 3)
    return bytes_written;

  out[0] = (in >> 8) & 0xff;
  out[1] = (in >> 0) & 0xff;

  bytes_written = 2;

  return bytes_written;
}