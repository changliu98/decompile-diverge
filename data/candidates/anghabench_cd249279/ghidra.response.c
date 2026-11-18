int pid_to_processor_id(int pid)

{
  int i;
  int pid_local;
  
  i = 0;
  while( true ) {
    if (ncpus <= i) {
      return -1;
    }
    if (cpu_tasks[i].pid == pid) break;
    i = i + 1;
  }
  return i;
}