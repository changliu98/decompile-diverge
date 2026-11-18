int __cdecl pid_to_processor_id(int pid)
{
  int *tasks = (int *)cpu_tasks;

  for (int i = 0; i < ncpus; ++i)
  {
    if (tasks[i] == pid)
      return i;
  }
  return -1;
}