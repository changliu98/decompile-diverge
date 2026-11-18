int __cdecl test_and_set(int *target)
{
  int rv; // [rsp+0h] [rbp-Ch]

  rv = *target;
  *target = 1;
  return rv;
}