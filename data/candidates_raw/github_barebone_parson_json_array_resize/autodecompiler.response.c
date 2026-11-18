static int _json_array_resize(JSON_Array *array, size_t new_capacity) {
    JSON_Value **new_items = NULL;
    int return_code;
    if (new_capacity == 0) {
        return_code = -1;
    } else {
        new_items = (JSON_Value**)parson_malloc(sizeof(JSON_Value*) * new_capacity);
        if (new_items == NULL) {
            return_code = -1;
        } else {
            if (array->items && array->count > 0) {
                memcpy(new_items, array->items, sizeof(JSON_Value*) * array->count);
            }
            parson_free(array->items);
            array->items = new_items;
            array->capacity = new_capacity;
            return_code = 0;
        }
    }
    return return_code;
}