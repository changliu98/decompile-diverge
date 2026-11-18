int get_cu_id(int total_cu_count)
{
  int cu_id = gpu_processor_id_low;
  gpu_processor_id_low += total_cu_count;
  return cu_id;
}