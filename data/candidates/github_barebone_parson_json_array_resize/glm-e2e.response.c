int json_array_resize(struct json_array *array, size_t new_capacity) {
    void **new_items = NULL;
    int ret;

    if (new_capacity == 0) {
        ret = -1;
        goto end;
    }

    new_items = malloc(new_capacity * 8);
    if (new_items == NULL) {
        ret = -1;
        goto end;
    }

    if (array->items != NULL && array->count > 0) {
        memcpy(new_items, array->items, array->count * 8);
    }

    free(array->items);
    array->items = new_items;
    array->capacity = new_capacity;
    ret = 0;

end:
    return ret;
}