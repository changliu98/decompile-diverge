intptr_t
atomic_fetch_and (intptr_t *object, intptr_t operand)
{
  intptr_t result = *object;
  *object &= operand;
  return result;
}