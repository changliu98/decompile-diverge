JSON_Status json_object_grow_and_rehash(JSON_Object *object)

{
  JSON_Value *value_00;
  JSON_Status JVar1;
  JSON_Value *pJVar2;
  size_t local_98;
  JSON_Status res;
  size_t new_capacity;
  uint i;
  JSON_Value *value;
  char *key;
  JSON_Object new_object;
  JSON_Value *wrapping_value;
  JSON_Object *object_local;
  JSON_Status local_c;
  
  if (object->cell_capacity << 1 < 0x11) {
    local_98 = 0x10;
  }
  else {
    local_98 = object->cell_capacity << 1;
  }
  JVar1 = json_object_init(&new_object,local_98);
  if (JVar1 == 0) {
    pJVar2 = json_object_get_wrapping_value(object);
    new_object.wrapping_value = pJVar2;
    for (i = 0; (ulong)i < object->count; i = i + 1) {
      value_00 = object->values[i];
      JVar1 = json_object_add(&new_object,object->names[i],value_00);
      if (JVar1 != 0) {
        json_object_deinit(&new_object,0,0);
        return -1;
      }
      value_00->parent = pJVar2;
    }
    json_object_deinit(object,0,0);
    memcpy(object,&new_object,0x48);
    local_c = 0;
  }
  else {
    local_c = -1;
  }
  return local_c;
}