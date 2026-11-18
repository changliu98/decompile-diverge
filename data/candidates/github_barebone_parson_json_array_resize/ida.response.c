JSON_Status __cdecl json_array_resize(JSON_Array *array, size_t new_capacity)
{
  JSON_Value **new_items; // [rsp+0h] [rbp-20h]

  if ( !new_capacity )
    return -1;
  new_items = (JSON_Value **)parson_malloc(8 * new_capacity);
  if ( !new_items )
    return -1;
  if ( array->items && array->count )
    memcpy(new_items, array->items, 8 * array->count);
  parson_free(array->items);
  array->items = new_items;
  array->capacity = new_capacity;
  return 0;
}