int get_and_inc_gpu_processor_id(int n) {
  int ret;
  ret = gpu_processor_id;
  gpu_processor_id += n;
  return ret;
}