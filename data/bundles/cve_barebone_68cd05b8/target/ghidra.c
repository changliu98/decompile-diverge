njs_jump_off_t njs_vmcode_typeof(njs_vm_t *vm,njs_value_t *value,njs_value_t *invld)

{
  njs_value_t *pnVar1;
  njs_value_t *invld_local;
  njs_value_t *value_local;
  njs_vm_t *vm_local;
  
  pnVar1 = njs_vmcode_typeof::types[(value->data).type];
  *(undefined8 *)&vm->retval = *(undefined8 *)pnVar1;
  (vm->retval).data.u = *(anon_union_8_16_5fa0025e_for_u *)((long)pnVar1 + 8);
  return 0x18;
}