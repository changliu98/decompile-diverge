int get_ip_class(unsigned int ip)
{
  return (ip & 0xff000000) >> 24;
}