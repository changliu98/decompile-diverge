static inline int cpu_core_index_of_thread(int thread_id) {
  return thread_id >> thread_id_shift;
}