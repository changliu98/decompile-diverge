int cpu_map__id_to_socket(int id)

{
  int id_local;
  
  return id >> 0x10;
}