static njs_int_t njs_array_convert_to_slow_array(njs_vm_t *vm,
                                                 njs_array_t *array) {
  njs_object_prop_t props, index;
  njs_property_t *prop;
  njs_uint_t i, n;
  njs_set_array(&props, array);
  array->elts.length = 0;
  n = array->length;
  for (i = 0; i < n; i++) {
    if (array->start[i].type != 7) {
      njs_uint32_to_string(&index, i);
      prop = njs_object_property_add(vm, &props, &index, 0);
      if (prop == NULL) {
        return -1;
      }
      prop->value = array->start[i];
    }
  }
  njs_mp_free(vm->mem_pool, array->start);
  array->start = NULL;
  return 0;
}