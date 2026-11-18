njs_int_t __cdecl njs_array_convert_to_slow_array(njs_vm_t *vm, njs_array_t *array)
{
  njs_value_t *v2; // rcx
  njs_object_prop_t *prop; // [rsp+8h] [rbp-48h]
  njs_value_t value; // [rsp+10h] [rbp-40h] BYREF
  njs_value_t index; // [rsp+20h] [rbp-30h] BYREF
  uint32_t length; // [rsp+30h] [rbp-20h]
  uint32_t i; // [rsp+34h] [rbp-1Ch]
  njs_array_t *arraya; // [rsp+38h] [rbp-18h]
  njs_vm_t *vma; // [rsp+40h] [rbp-10h]

  vma = vm;
  arraya = array;
  njs_set_array(&value, array);
  *(_BYTE *)&arraya->object &= ~1u;
  length = arraya->length;
  for ( i = 0; i < length; ++i )
  {
    if ( arraya->start[i].data != 7 )
    {
      njs_uint32_to_string(&index, i);
      prop = njs_object_property_add(vma, &value, &index, 0);
      if ( !prop )
        return -1;
      v2 = &arraya->start[i];
      *(_QWORD *)&prop->value.data = v2->data;
      prop->value.data.u.object = v2->data.u.object;
    }
  }
  njs_mp_free(vma->mem_pool, arraya->start);
  arraya->start = 0LL;
  return 0;
}