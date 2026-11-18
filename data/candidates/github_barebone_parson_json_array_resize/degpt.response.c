JSON_Status json_array_resize(JSON_Array *array, size_t new_capacity)
{
    // Return error if the requested new capacity is zero
    if (new_capacity == 0) {
        return -1;
    }

    // Allocate memory for the new array of JSON_Value pointers
    // Each pointer is 8 bytes (64-bit), hence the shift by 3 (multiply by 8)
    JSON_Value **new_items = (JSON_Value **)(*parson_malloc)(new_capacity << 3);
    if (new_items == NULL) {
        // Return error if memory allocation fails
        return -1;
    }

    // Copy existing items to the new array if there are any items
    if (array->items != NULL && array->count != 0) {
        // Copy 'count' items, each being 8 bytes (pointer size)
        memcpy(new_items, array->items, array->count << 3);
    }

    // Free the old array items
    (*parson_free)(array->items);
    // Update the array's items pointer to the new memory block
    array->items = new_items;
    // Update the array's capacity to the new capacity
    array->capacity = new_capacity;

    // Return success
    return 0;
}