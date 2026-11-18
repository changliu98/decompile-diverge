JSON_Status __cdecl json_object_grow_and_rehash(JSON_Object *object)
{
  size_t new_capacity;
  unsigned int i;
  JSON_Value *value;
  JSON_Object new_object; 
  JSON_Value *wrapping_value;

  wrapping_value = NULL;
  
  // Calculate the new capacity (double the current, with a minimum of 16)
  if (object->cell_capacity * 2 <= 16)
    new_capacity = 16;
  else
    new_capacity = object->cell_capacity * 2;

  if (json_object_init(&new_object, new_capacity))
    return JSONFailure;

  // Preserve the original wrapping value (dwarf_errno is a decompiler artifact)
  wrapping_value = object->wrapping_value;
  new_object.wrapping_value = wrapping_value;

  // Rehash all existing key-value pairs into the new object
  for (i = 0; i < object->count; ++i)
  {
    value = object->values[i];
    if (json_object_add(&new_object, object->names[i], value))
    {
      json_object_deinit(&new_object, 0, 0);
      return JSONFailure;
    }
    value->parent = wrapping_value;
  }

  // Free the old object's internal allocations, then copy the new object's data over
  json_object_deinit(object, 0, 0);
  memcpy(object, &new_object, sizeof(JSON_Object));
  
  return JSONSuccess;
}