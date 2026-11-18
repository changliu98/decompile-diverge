unsigned int get_and_inc_gpu_processor_id(unsigned int cu_count)
{
    unsigned int id = gpu_processor_id_low;
    gpu_processor_id_low += cu_count;
    return id;
}