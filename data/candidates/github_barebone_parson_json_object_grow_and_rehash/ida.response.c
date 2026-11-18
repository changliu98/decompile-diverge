JSON_Status __cdecl json_object_grow_and_rehash(JSON_Object *object)
{
  size_t v2; // [rsp+0h] [rbp-90h]
  unsigned int i; // [rsp+1Ch] [rbp-74h]
  JSON_Value *value; // [rsp+20h] [rbp-70h]
  JSON_Object new_object; // [rsp+30h] [rbp-60h] BYREF
  JSON_Value *wrapping_value; // [rsp+78h] [rbp-18h]
  JSON_Object *objecta; // [rsp+80h] [rbp-10h]

  objecta = object;
  wrapping_value = 0LL;
  if ( 2 * object->cell_capacity <= 0x10 )
    v2 = 16LL;
  else
    v2 = 2 * objecta->cell_capacity;
  if ( json_object_init(&new_object, v2) )
    return -1;
  wrapping_value = dwarf_errno(objecta);
  new_object.wrapping_value = wrapping_value;
  for ( i = 0; i < objecta->count; ++i )
  {
    value = objecta->values[i];
    if ( json_object_add(&new_object, objecta->names[i], value) )
    {
      json_object_deinit(&new_object, 0, 0);
      return -1;
    }
    value->parent = wrapping_value;
  }
  json_object_deinit(objecta, 0, 0);
  memcpy(objecta, &new_object, sizeof(JSON_Object));
  return 0;
}