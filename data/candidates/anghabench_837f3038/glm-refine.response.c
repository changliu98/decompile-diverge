void memcached_udp_set_cookie(unsigned char *buf, size_t length, uint64_t seqno)
{
  if (length >= 2)
  {
    buf[0] = (unsigned char)(seqno >> 8);
    buf[1] = (unsigned char)seqno;
  }
}