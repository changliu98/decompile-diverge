njs_jump_off_t
njs_vmcode_array(njs_vm_t *vm, u_char *pc)
{
 njs_array_t *array;
 njs_value_t *vp;
 uint32_t i;

 if ((array = njs_array_alloc(vm, 0, *(uint64_t *)(pc + 2 * sizeof(uint32_t)),
     8)) == NULL)
  return -1;

 if (*(pc + 3 * sizeof(uint32_t))) {
  for (vp = array->start, i = array->length; i != 0; i--, vp++)
   (vp->data).type = 7;
 } else {
  array->length = 0;
 }

 njs_set_array(&vm->retval, array);
 return 4 * sizeof(uint32_t);
}