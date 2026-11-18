njs_int_t njs_vmcode_array(njs_vm_t *vm, njs_chb_t *args) {
  njs_array_t *array;
  njs_value_t *value;
  unsigned n;
  array = njs_array_alloc(vm, NULL, args[1].length, 8);
  if (array == NULL) {
    return -1;
  }
  if (args[2].length32 == 0) {
    array->nelts = 0;
  } else {
    value = array->elts;
    n = array->nelts;
    do {
      value->type = 7;
      value++;
    } while (--n);
  }
  njs_set_array(&vm->retval, array);
  return 32;
}