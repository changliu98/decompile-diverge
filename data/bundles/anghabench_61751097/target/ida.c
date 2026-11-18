bool __cdecl setsockopt_needs_rtnl(int optname)
{
  return (unsigned int)(optname - 128) <= 0xB;
}