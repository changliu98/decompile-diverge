int get_and_inc_gpu_processor_id(int offset) {
    int ret = buffer[offset];
    ip = offset + ip;
    return ret;
}