static int c_sysconf_(int *argp, int *resultp, int *errnop)
{
  int res;
  res = sysconf(*argp);
  *resultp = res;
  *errnop = (*__errno_location ());
  return;
}