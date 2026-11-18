int get_and_inc_gpu_processor_id(int total_cpu_cores)
{
 int cpu_processor_id = gpu_processor_id_low;
 gpu_processor_id_low += total_cpu_cores;

 return cpu_processor_id;
}