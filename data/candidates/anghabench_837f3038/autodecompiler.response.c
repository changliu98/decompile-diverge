int
memcached_udp_set_cookie(char *buf, size_t len, unsigned long seqno)
{
 int ret;

 if (len < 3) {
  ret = 0;
 } else {
  buf[0] = (seqno >> 8) & 0xff;
  buf[1] = (seqno >> 0) & 0xff;
  ret = 0;
 }

 return ret;
}