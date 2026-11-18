static int njs_vmcode_typeof(struct njs_vm *vm, struct njs_value *val, struct njs_value *invld)
{
  vm->retval = njs_value_new_string(&vm->heap, njs_vmcode_typeof_types[*val].name);
  return 24;
}