njs_jump_off_t njs_vmcode_array(njs_vm_t *vm,u_char *pc)

{
  njs_array_t *array_00;
  njs_vmcode_array_t *code;
  njs_value_t *value;
  njs_array_t *array;
  uint32_t length;
  u_char *pc_local;
  njs_vm_t *vm_local;
  njs_jump_off_t local_10;
  
  array_00 = njs_array_alloc(vm,0,*(uint64_t *)(pc + 0x10),8);
  if (array_00 == (njs_array_t *)0x0) {
    local_10 = -1;
  }
  else {
    if (pc[0x18] == '\0') {
      array_00->length = 0;
    }
    else {
      value = array_00->start;
      length = array_00->length;
      do {
        (value->data).type = 7;
        value = value + 1;
        length = length - 1;
      } while (length != 0);
    }
    njs_set_array(&vm->retval,array_00);
    local_10 = 0x20;
  }
  return local_10;
}