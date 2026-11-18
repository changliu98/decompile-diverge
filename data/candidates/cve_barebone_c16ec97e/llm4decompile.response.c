int
njs_array_convert_to_slow_array(njs_vm_t *vm, njs_array_t *array)
{
  njs_value_t value;
  njs_value_t index;
  njs_object_prop_t *prop;
  unsigned int i;

  njs_set_array(&value, array);
  array->fast_array = 0;

  for (i = 0; i < array->length; i++) {
    if (array->start[i].data.type == 7)
      continue;

    njs_uint32_to_string(&index, i);
    prop = njs_object_property_add(vm, &value, &index, 0);
    if (prop == NULL)
      return -1;

    prop->value = array->start[i];
  }

  njs_mp_free(vm->mem_pool, array->start);
  array->start = NULL;

  return 0;
}