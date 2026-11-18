void ulimit_stack(long *cur, long *max, int *err) {
  struct rlimit rl;
  int rc;
  rl.rlim_cur = (rlim_t)-1;
  rl.rlim_max = (rlim_t)-1;
  rc = setrlimit(RLIMIT_STACK, &rl);
  if (rc == -1) {
    rc = getrlimit(RLIMIT_STACK, &rl);
    if (rc == 0) {
      rl.rlim_cur = rl.rlim_max;
      rc = setrlimit(RLIMIT_STACK, &rl);
    }
  }
  *err = rc;
  *cur = (rlim_t)-1;
  *max = (rlim_t)-1;
  rc = getrlimit(RLIMIT_STACK, &rl);
  if (rc == 0) {
    *cur = rl.rlim_cur;
    *max = rl.rlim_max;
  }
}