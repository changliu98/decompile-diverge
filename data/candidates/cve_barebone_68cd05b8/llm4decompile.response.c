uint32_t
njs_vmcode_typeof(njs_vm_t *vm, njs_value_t *value, njs_value_t *invld)
{
  vm->retval = njs_vmcode_typeof::types[value->type];
  return 0x18;
}