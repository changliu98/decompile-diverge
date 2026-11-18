unsigned int __cdecl memcached_udp_set_cookie(unsigned __int8 *px, size_t length, uint64_t seqno)
{
  if ( length >= 2 )
  {
    *px = BYTE1(seqno);
    px[1] = seqno;
  }
  return 0;
}