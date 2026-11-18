int njs_array_convert_to_slow_array(struct njs_vm *vm, struct njs_array *array)
{
  struct njs_value val; struct njs_value idx;
  struct njs_object_prop *prop;
  unsigned int i; unsigned int len;
  njs_array_tovalue(&val, array);
  array->object = 0;
  len = array->length;
  for (i = 0; i < len; i++) {
    if (array->start[i].data.type == njs_undefined) {
      continue;
    }
    njs_value_fromint(&idx, i);
    prop = njs_object_set(vm, &val, &idx, 0);
    if (prop == ((void *)0)) {
      return -1;
    }
    prop->value = array->start[i];
  }
  njs_array_destroy(vm->mem_pool, array->start);
  array->start = ((void *)0);
  return 0;
}