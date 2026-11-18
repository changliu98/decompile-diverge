int json_object_resize(JSON_Object *object)
{
    size_t new_capacity;
    JSON_Object new_object;
    int result;
    unsigned long long errno_value = 0;
    char *key = NULL;
    JSON_Value *value = NULL;
    unsigned int i = 0;

    if (object->capacity * 2 > 16) {
        new_capacity = object->capacity * 2;
    } else {
        new_capacity = 16;
    }
    result = json_object_init(&new_object, new_capacity);
    if (result != 0) {
        return -1;
    }
    new_object.error_number = errno_value = dwarf_errno(object);
    for (i = 0; i < object->item_count; i++) {
        key = object->keys[i];
        value = object->values[i];
        result = json_object_add(&new_object, key, value);
        if (result != 0) {
            json_object_deinit(&new_object, NULL, NULL);
            return -1;
        }
        value->error_number = errno_value;
    }
    json_object_deinit(object, NULL, NULL);
    memcpy(object, &new_object, sizeof(JSON_Object));
    return 0;
}