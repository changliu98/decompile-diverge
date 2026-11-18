int pid_to_processor_id(int task)
{
  int i;
  for (i = 0; i < ncpus; i++)
    if (cpu_tasks[i] == task)
      return i;
  return -1;
}