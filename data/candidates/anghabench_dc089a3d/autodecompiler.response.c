int cpu_map__id_to_socket(int ver)
{
 return (ver >> 16);
}