int cpu_map__id_to_cpu(int id)

{
  int id_local;
  
  return id & 0xffff;
}