static int setsockopt_needs_rtnl(int opt)
{
  return (opt >= 0x80 && opt <= 0x8f);
}