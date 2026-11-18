void __cdecl ulimit_stack(long *rlim_cur, long *rlim_max, int *ierr)
{
  rlimit rlim; // [rsp+0h] [rbp-30h] BYREF
  int result; // [rsp+14h] [rbp-1Ch]
  int *ierra; // [rsp+18h] [rbp-18h]
  long *rlim_maxa; // [rsp+20h] [rbp-10h]
  long *rlim_cura; // [rsp+28h] [rbp-8h]

  rlim_cura = rlim_cur;
  rlim_maxa = rlim_max;
  ierra = ierr;
  rlim.rlim_cur = -1LL;
  rlim.rlim_max = -1LL;
  result = setrlimit(__rlimit_resource::RLIMIT_STACK, &rlim);
  if ( result == -1 && !getrlimit(__rlimit_resource::RLIMIT_STACK, &rlim) )
  {
    rlim.rlim_cur = rlim.rlim_max;
    result = setrlimit(__rlimit_resource::RLIMIT_STACK, &rlim);
  }
  *ierra = result;
  *rlim_cura = -1LL;
  *rlim_maxa = -1LL;
  if ( !getrlimit(__rlimit_resource::RLIMIT_STACK, &rlim) )
  {
    *rlim_cura = rlim.rlim_cur;
    *rlim_maxa = rlim.rlim_max;
  }
}