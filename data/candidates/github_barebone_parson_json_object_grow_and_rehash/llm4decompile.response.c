JSON_Status json_object_grow_and_rehash(JSON_Object *object)
{
    JSON_Object new_object;
    JSON_Status res;
    size_t new_capacity = object->cell_capacity * 2;
    if (new_capacity < 16)
        new_capacity = 16;
    res = json_object_init(&new_object, new_capacity);
    if (res != 0)
        return -1;
    new_object.wrapping_value = json_object_get_wrapping_value(object);
    for (unsigned int i = 0; i < object->count; i++)
    {
        JSON_Value *value = object->values[i];
        res = json_object_add(&new_object, object->names[i], value);
        if (res != 0)
        {
            json_object_deinit(&new_object, NULL, NULL);
            return -1;
        }
        value->parent = new_object.wrapping_value;
    }
    json_object_deinit(object, NULL, NULL);
    memcpy(object, &new_object, sizeof(JSON_Object));
    return 0;
}