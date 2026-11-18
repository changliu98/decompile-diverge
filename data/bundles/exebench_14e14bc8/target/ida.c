void __cdecl c_sysconf_(int *name, int *val, int *err)
{
  *val = sysconf(*name);
  *err = *__errno_location();
}