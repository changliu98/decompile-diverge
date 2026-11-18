int get_priority(pid_t pid, int *priority) {
  *priority = getpriority(PRIO_PROCESS, pid);
  return errno;
}