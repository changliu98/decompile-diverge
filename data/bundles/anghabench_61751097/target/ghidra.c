bool setsockopt_needs_rtnl(int optname)

{
  int optname_local;
  uint local_c;
  
  local_c = (uint)(optname - 0x80U < 0xc);
  return local_c;
}