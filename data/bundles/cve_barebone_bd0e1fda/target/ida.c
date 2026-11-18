njs_jump_off_t __cdecl njs_vmcode_array(njs_vm_t *vm, u_char *pc)
{
  njs_value_t *value; // [rsp+10h] [rbp-30h]
  njs_array_t *array; // [rsp+18h] [rbp-28h]
  uint32_t length; // [rsp+24h] [rbp-1Ch]

  array = njs_array_alloc(vm, 0LL, *((_QWORD *)pc + 2), 8u);
  if ( !array )
    return -1LL;
  if ( pc[24] )
  {
    value = array->start;
    length = array->length;
    do
    {
      *(_BYTE *)&value->data = 7;
      ++value;
      --length;
    }
    while ( length );
  }
  else
  {
    array->length = 0;
  }
  njs_set_array(&vm->retval, array);
  return 32LL;
}