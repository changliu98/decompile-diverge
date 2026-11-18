intptr_t __cdecl atomic_fetch_add(intptr_t *object, intptr_t operand)
{
  intptr_t ret; // [rsp+0h] [rbp-18h]

  ret = *object;
  *object += operand;
  return ret;
}