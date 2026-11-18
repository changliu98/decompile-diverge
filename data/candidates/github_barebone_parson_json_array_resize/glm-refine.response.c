JSON_Status __cdecl json_array_resize(JSON_Array *array, size_t new_capacity) {
    JSON_Value **new_items;

    // Prevent allocation of zero bytes
    if (new_capacity == 0) {
        return JSONFailure;
    }

    // Allocate new memory block for the array items
    new_items = (JSON_Value **)parson_malloc(sizeof(JSON_Value *) * new_capacity);
    if (new_items == NULL) {
        return JSONFailure;
    }

    // Copy existing items to the new memory block if any exist
    if (array->items != NULL && array->count > 0) {
        memcpy(new_items, array->items, sizeof(JSON_Value *) * array->count);
    }

    // Free the old memory block and update the array metadata
    parson_free(array->items);
    array->items = new_items;
    array->capacity = new_capacity;

    return JSONSuccess;
}