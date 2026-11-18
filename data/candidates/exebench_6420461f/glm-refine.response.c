void __cdecl ulimit_stack(long *rlim_cur, long *rlim_max, int *ierr)
{
  rlimit rlim; 
  int result;

  // Attempt to set the stack limit to unlimited (RLIM_INFINITY)
  rlim.rlim_cur = -1LL;
  rlim.rlim_max = -1LL;
  result = setrlimit(RLIMIT_STACK, &rlim);

  // If setting to unlimited fails, try to set it to the current maximum limit
  if (result == -1 && !getrlimit(RLIMIT_STACK, &rlim))
  {
    rlim.rlim_cur = rlim.rlim_max;
    result = setrlimit(RLIMIT_STACK, &rlim);
  }

  // Output the result of the setrlimit operation
  *ierr = result;

  // Initialize the output limits to unlimited (RLIM_INFINITY)
  *rlim_cur = -1LL;
  *rlim_max = -1LL;

  // Retrieve and output the current stack limits
  if (!getrlimit(RLIMIT_STACK, &rlim))
  {
    *rlim_cur = rlim.rlim_cur;
    *rlim_max = rlim.rlim_max;
  }
}