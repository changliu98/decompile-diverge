njs_int_t njs_array_convert_to_slow_array(njs_vm_t *vm,njs_array_t *array)

{
  njs_value_t *pnVar1;
  njs_object_prop_t *pnVar2;
  njs_object_prop_t *prop;
  njs_value_t value;
  njs_value_t index;
  uint32_t length;
  uint32_t i;
  njs_array_t *array_local;
  njs_vm_t *vm_local;
  
  array_local = array;
  vm_local = vm;
  njs_set_array(&value,array);
  array_local.fast_array = '\0';
  length = array_local->length;
  i = 0;
  do {
    if (length <= i) {
      njs_mp_free(vm_local->mem_pool,array_local->start);
      array_local->start = (njs_value_t *)0x0;
      return 0;
    }
    if (array_local->start[i].data.type != 7) {
      njs_uint32_to_string(&index,i);
      pnVar2 = njs_object_property_add(vm_local,&value,&index,0);
      if (pnVar2 == (njs_object_prop_t *)0x0) {
        return -1;
      }
      pnVar1 = array_local->start;
      *(undefined8 *)&pnVar2->value = *(undefined8 *)(pnVar1 + i);
      (pnVar2->value).data.u = pnVar1[i].data.u;
    }
    i = i + 1;
  } while( true );
}