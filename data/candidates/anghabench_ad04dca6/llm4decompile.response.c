int cpu_core_index_of_thread(int cpu)
{
	return cpu >> threads_shift;
}