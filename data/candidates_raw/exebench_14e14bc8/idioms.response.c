static int sysconf_call(int *argp, int *resultp, int *errnop)
{
  int res;
  res = sysconf(*argp);
  *resultp = res;
  *errnop = (*__errno_location ());
  return;
}