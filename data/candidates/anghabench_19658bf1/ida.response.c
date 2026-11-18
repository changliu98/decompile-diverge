unsigned int __cdecl get_and_inc_gpu_processor_id(unsigned int total_cu_count)
{
  int current_id; // [rsp+0h] [rbp-8h]

  current_id = gpu_processor_id_low;
  gpu_processor_id_low += total_cu_count;
  return current_id;
}