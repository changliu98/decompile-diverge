static JSON_Status json_object_grow_and_rehash(JSON_Object *object) {
    JSON_Value *wrapping_value = NULL;
    JSON_Object new_object;
    char *key = NULL;
    JSON_Value *value = NULL;
    unsigned int i = 0;
    size_t new_capacity = MAX(object->cell_capacity * 2, STARTING_CAPACITY);
    JSON_Status res = json_object_init(&new_object, new_capacity);
    if (res != JSONSuccess) {
        return JSONFailure;
    }

    wrapping_value = json_object_get_wrapping_value(object);
    new_object.wrapping_value = wrapping_value;

    for (i = 0; i < object->count; i++) {
        key = object->names[i];
        value = object->values[i];
        res = json_object_add(&new_object, key, value);
        if (res != JSONSuccess) {
            json_object_deinit(&new_object, PARSON_FALSE, PARSON_FALSE);
            return JSONFailure;
        }
        value->parent = wrapping_value;
    }
    json_object_deinit(object, PARSON_FALSE, PARSON_FALSE);
    *object = new_object;
    return JSONSuccess;
}