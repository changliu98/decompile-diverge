void ulimit_stack(long int *rlim_cur, long int *rlim_max, int *ierr) {

  int result;
  struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};







  result = setrlimit(RLIMIT_STACK, &rlim);
  if (result == -1) {

    if (getrlimit(RLIMIT_STACK, &rlim) == 0) {
        rlim.rlim_cur = rlim.rlim_max;
        result = setrlimit(RLIMIT_STACK, &rlim);
    }
  }

  *ierr = result;
  *rlim_cur = -1;
  *rlim_max = -1;
  if (getrlimit(RLIMIT_STACK, &rlim) == 0) {
    *rlim_cur = rlim.rlim_cur;
    *rlim_max = rlim.rlim_max;
  }

}