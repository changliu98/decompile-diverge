void ulimit_stack(long *cur, long *max, int *err)
{
  struct rlimit rlim;
  int ret;
  rlim.rlim_cur = rlim.rlim_max = ((__rlim_t) -1);
  ret = setrlimit(RLIMIT_STACK, &rlim);
  if (ret == -1 && getrlimit(RLIMIT_STACK, &rlim) == 0) {
    rlim.rlim_cur = rlim.rlim_max;
    ret = setrlimit(RLIMIT_STACK, &rlim);
  }
  *err = ret;
  *cur = *max = ((__rlim_t) -1);
  if (getrlimit(RLIMIT_STACK, &rlim) == 0) {
    *cur = rlim.rlim_cur;
    *max = rlim.rlim_max;
  }
}