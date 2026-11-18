JSON_Status json_array_resize(JSON_Array *array,size_t new_capacity)

{
  JSON_Value **__dest;
  JSON_Value **new_items;
  size_t new_capacity_local;
  JSON_Array *array_local;
  JSON_Status local_c;
  
  if (new_capacity == 0) {
    local_c = -1;
  }
  else {
    __dest = (*parson_malloc)(new_capacity << 3);
    if (__dest == (JSON_Value **)0x0) {
      local_c = -1;
    }
    else {
      if ((array->items != (JSON_Value **)0x0) && (array->count != 0)) {
        memcpy(__dest,array->items,array->count << 3);
      }
      (*parson_free)(array->items);
      array->items = __dest;
      array->capacity = new_capacity;
      local_c = 0;
    }
  }
  return local_c;
}