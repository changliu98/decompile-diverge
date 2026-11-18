void __cdecl c_sysconf_(int *name, int *val, int *err)
{
  *val = sysconf(*name);
  *err = errno;
}