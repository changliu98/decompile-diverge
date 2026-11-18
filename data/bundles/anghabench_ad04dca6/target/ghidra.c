int cpu_core_index_of_thread(int cpu)

{
  int cpu_local;
  
  return cpu >> ((byte)threads_shift & 0x1f);
}