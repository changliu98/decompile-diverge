int memcached_udp_set_cookie(int pcap_fd, unsigned char *rfmon, unsigned long size, unsigned long seqno)
{
  if (size < 2)
    return 0;
  rfmon[0] = (unsigned char)(seqno >> 8);
  rfmon[1] = (unsigned char)(seqno);
  return 0;
}