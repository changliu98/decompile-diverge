uint get_and_inc_gpu_processor_id(uint total_cu_count)

{
  uint uVar1;
  int current_id;
  uint total_cu_count_local;
  
  uVar1 = gpu_processor_id_low;
  gpu_processor_id_low = total_cu_count + gpu_processor_id_low;
  return uVar1;
}