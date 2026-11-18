void ulimit_stack(long *rlim_cur, long *rlim_max, int *ierr)
{
  struct rlimit rlim;
  int err;

  rlim.rlim_cur = 1024L * 1024L * 1024L;
  rlim.rlim_max = 1024L * 1024L * 1024L;
  err = setrlimit(RLIMIT_STACK, &rlim);
  if (err == -1 && getrlimit(RLIMIT_STACK, &rlim) == 0) {
    rlim.rlim_cur = rlim.rlim_max;
    err = setrlimit(RLIMIT_STACK, &rlim);
  }
  *ierr = err;

  *rlim_cur = -1;
  *rlim_max = -1;
  if (getrlimit(RLIMIT_STACK, &rlim) == 0) {
    *rlim_cur = (long) rlim.rlim_cur;
    *rlim_max = (long) rlim.rlim_max;
  }
}