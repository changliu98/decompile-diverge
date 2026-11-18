int get_and_inc_gpu_processor_id(int inc_val) {
    int old_val = gpu_processor_id_low;
    gpu_processor_id_low += inc_val;
    return old_val;
}