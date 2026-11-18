static inline int get_thread_id(int cpu)
{
  return cpu / threads_shift;
}