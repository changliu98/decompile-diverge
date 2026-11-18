intptr_t atomic_fetch_add(intptr_t *object,intptr_t operand)

{
  intptr_t iVar1;
  intptr_t ret;
  intptr_t operand_local;
  intptr_t *object_local;
  
  iVar1 = *object;
  *object = *object + operand;
  return iVar1;
}