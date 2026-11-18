intptr_t __cdecl atomic_fetch_xor(intptr_t *object, intptr_t operand)
{
  intptr_t old_value = *object;
  *object ^= operand;
  return old_value;
}