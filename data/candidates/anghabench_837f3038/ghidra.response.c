uint memcached_udp_set_cookie(uchar *px,size_t length,uint64_t seqno)

{
  uint64_t seqno_local;
  size_t length_local;
  uchar *px_local;
  
  if (1 < length) {
    *px = (uchar)(seqno >> 8);
    px[1] = (uchar)seqno;
  }
  return 0;
}