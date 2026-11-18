int __cdecl test_and_set(int *target)
{
  int old_val = *target;
  *target = 1;
  return old_val;
}