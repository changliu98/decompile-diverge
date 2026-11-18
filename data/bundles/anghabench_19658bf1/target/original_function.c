unsigned int get_and_inc_gpu_processor_id(
				unsigned int total_cu_count)
{
	int current_id = gpu_processor_id_low;

	gpu_processor_id_low += total_cu_count;
	return current_id;
}