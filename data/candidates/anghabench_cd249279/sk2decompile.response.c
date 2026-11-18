int pid_to_processor_id(int pid) {
  int i;
  for (i = 0; i < nr_processors; i++) {
    if (processor_pid[i] == pid) return i;
  }
  return -1;
}