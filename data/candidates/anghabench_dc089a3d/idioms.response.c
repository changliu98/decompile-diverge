int cpu_map__id_to_socket(unsigned int ip)
{
  return (ip & 0xff000000) >> 24;
}