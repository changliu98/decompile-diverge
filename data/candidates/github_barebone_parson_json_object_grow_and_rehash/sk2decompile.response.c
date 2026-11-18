static Dwarf_Signed json_object_grow_and_rehash(Json_Object *object) {
  Json_Object new_object;
  Json_Value *errno_value = NULL;
  unsigned int i;
  if (json_object_init(&new_object,
                       object->capacity * 2 > 16 ? object->capacity * 2 : 16)) {
    return -1;
  }
  new_object.errno_value = errno_value = dwarf_errno(object);
  for (i = 0; i < object->size; ++i) {
    Json_Value *value = object->values[i];
    if (json_object_add(&new_object, object->names[i], value)) {
      json_object_deinit(&new_object, NULL, NULL);
      return -1;
    }
    value->errno_value_parent = errno_value;
  }
  json_object_deinit(object, NULL, NULL);
  memcpy(object, &new_object, sizeof(Json_Object));
  return 0;
}